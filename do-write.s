;  ci-write.s -- Write request data.
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

.include "cbm_kernal.inc"

.autoimport on
.importzp	sp
.importzp	tmp1, tmp2, ptr1
.export		_do_write

; void __near__ do_write (unsigned char id, __near__ const unsigned char *, unsigned int)

.segment	"CODE"

.proc	_do_write: near

.segment	"CODE"

	sta tmp1
    stx tmp2
	ldy #$01
	lda (sp),y
	sta ptr1
	iny
	lda (sp),y
	sta ptr1 + 1
    ldx #$00
    lda (sp),y
    tax
    jsr CKOUT
    ldx tmp2
write_page:
	txa
	beq write_rest
	dex
	ldy #$00
loop_page:
	lda (ptr1),y
	jsr BSOUT
	iny
	bne loop_page
	inc ptr1 + 1
	jmp write_page
write_rest:
	lda tmp1
	beq end
	ldy #$00
loop_rest:
	lda (ptr1),y
	jsr BSOUT
	iny
	cpy tmp1
	bne loop_rest
end:
    jsr CLRCH
	jmp incsp3

.endproc

