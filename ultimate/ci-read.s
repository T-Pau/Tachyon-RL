;  ci-read.s -- Read request data.
;  Copyright (C) 2020 Dieter Baron
;
;  This file is part of ultimate, a cc65 implementation of the
;  Ultimate II command interface.
;  The authors can be contacted at <ultimate@tpau.group>.
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

.autoimport on
.importzp    sp
.importzp    ptr1, ptr2
.export        _ultimate_ci_read

; void __near__ ultimate_ci_read(__near__ unsigned char *buffer, unsigned int length)

.segment    "CODE"

.proc    _ultimate_ci_read: near

.segment    "CODE"

        sta ptr2
        stx ptr2 + 1
        ldy #$00
        sty ptr1
        lda (sp),y
        tax
        clc
        adc ptr2
        sta ptr2
        iny
        lda (sp),y
        sta ptr1 + 1
        adc ptr2 + 1
        sta ptr2 + 1
        txa
        tay
loop:
        lda $df1c
        and #$20
        beq end
loop_packet:
        lda $df1c
        bpl end_packet
        lda $df1e
        sta (ptr1),y
        iny
        bne l1
        inc ptr1 + 1
l1:
        cpy ptr2
        bne loop_packet
        lda ptr1 + 1
        cmp ptr2 + 1
        bne loop_packet
        beq end
end_packet:
        lda #$02
        sta $df1c
busy_loop:
        lda $df1c
        and #$30
        cmp #$10
        beq busy_loop
        bne loop
end:
        sty ptr1
        ldy #$00
        lda (sp),y
        sta ptr2
        iny
        lda (sp),y
        sta ptr2 + 1
        sec
        lda ptr1
        sbc ptr2
        tay
        lda ptr1 + 1
        sbc ptr2 + 1
        tax
        tya
        jmp incsp2

.endproc
