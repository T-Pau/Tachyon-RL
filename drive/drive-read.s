;  drive-read.s -- Read from open file.
;  Copyright (C) 2020 Dieter Baron
;
;  This file is part of Tachyon RL, a backup program for your RAMLink.
;  The authors can be contacted at <tachyon-rl@tpau.group>.
;
;  Redistribution and use in source and binary forms, with or without
;  modification, are permitted provided that the following conditions
;  are met:
;  1. Redistributions of source code must retain the above copyright
;     notice, this list of conditions and the following disclaimer.
;  2. The names of the authors may not be used to endorse or promote
;     products derived from this software without specific prior
;     written permission.
;
;  THIS SOFTWARE IS PROVIDED BY THE AUTHORS ``AS IS'' AND ANY EXPRESS
;  OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
;  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
;  ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY
;  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
;  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
;  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
;  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
;  IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
;  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
;  IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

.include "cbm_kernal.inc"

.autoimport on
.importzp    sp
.importzp    ptr1, ptr2
.import     __oserror
.export        _drive_read

; uint16_t drive_read (uint8_t file, uint8_t *data, uint16_t length);

.segment    "CODE"

.proc    _drive_read: near

; Set up for copy:
;   put end address in ptr2
;   put current page in x and ptr1 (low byte always 0)
;   put current offset in page in y
;   select file for output
        sta ptr2
        stx ptr2 + 1
        ldy #$00
        lda (sp),y
        sta ptr1
        clc
        adc ptr2
        sta ptr2
        iny
        lda (sp),y
        sta ptr1 + 1
        adc ptr2 + 1
        sta ptr2 + 1
        iny
        lda (sp),y
        tax
        jsr CHKIN
        ldy ptr1
        bcs end ; TODO: set error
        lda #$00
        sta ptr1
        ldx ptr1 + 1

; read until end of page, unless we're at last page
read_page:
        cpx ptr2 + 1
        beq read_rest
        loop_page:
        jsr BASIN
        sta (ptr1),y
        lda $90 ; jsr READST ; TODO: assumes serial device
        bne end
        iny
        bne loop_page
        inx
        stx ptr1 + 1
        jmp read_page

; read incomplete last page
read_rest:
        lda ptr2
        beq end
loop_rest:
        jsr BASIN
        ; handle error
        sta (ptr1),y
        iny
        cpy ptr2
        bne loop_rest

end:
        ; remember end position and restore default output device
        sty ptr1
        jsr CLRCH

        ; calculate and return number of bytes copied
        ldy #0
        lda (sp),y
        sta ptr2
        iny
        lda (sp),y
        sta ptr2 + 1
        jsr incsp3

        sec
        lda ptr1
        sbc ptr2
        tay
        lda ptr1 + 1
        sbc ptr2 + 1
        tax
        tya
        rts

.endproc
