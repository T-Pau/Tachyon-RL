EN_SET_REC = $e0a9
RL_HW_EN = $e0b1
SET_REC_IMG = $fe03
ExEC_REC_REU = $fe06
EXEC_REC_SEC = $fe09
RL_HW_DIS = $fe0c
RL_HW_DIS2 = $fe0f
EXEC_REU_DIS = $fe1e
EXEC_SEC_DIS = $fe21

RL_REG_STATUS = $de00
RL_REG_COMMAND = $de01
RL_REG_COMPUTER = $de02
RL_REG_RAMLINK = $de04
RL_REG_LENGTH = $de07
RL_REG_ADDR_CONTROL = $de0a

REU_REG_STATUS = $df00
REU_REG_COMMAND = $df01
REU_REG_COMPUTER = $df02
REU_REG_RAMLINK = $df04
REU_REG_LENGTH = $df07
REU_REG_INTERRUPT = $df09
REU_REG_ADDR_CONTROL = $df0a

MODE_SAVE = 0
MODE_LOAD = 1

buffer = $1000
buffer_length = $8000

.code


.macro print_string addr
	ldx #<addr
	ldy #>addr
	jsr print_string_
.endmacro

.macro print_progress addr
	print_string addr
	; TODO: print progress
.endmacro

.zeropage
	.byte tmpaddr

.code
print_string_:
	stx tmpaddr
	sty tmpaddr + 1
	ldy #0
@loop:	lda (tmpaddr),y
	beq @end
	; TODO: chrout
	iny
	bne @loop
	inc tmpaddr + 1
	bne @loop
@end:	rts

get_reu_size:
; detects size of REU
; returns:
; 	a: 0: no REU present, 1: REU present
;	y: number of banks (64k) in REU (if present), 0 for 16m
;
; changes:
;	a, x, y
;	address
;	length
;	buffer

	ldx #$00
	stx address
	stx address + 1
	stx address + 2
	ldy #$01
	sty length
	stx length + 1
	ldy #0
	stx buffer
	lda #MODE_SAVE
	jsr reu_copy
	inc buffer
	lda #MODE_LOAD
	jsr reu_copy
	lda buffer
	beq @reu_size_loop
	lda #0
	rts

@reu_size_loop:
	iny
	beq @end
	sty address + 2
	sty buffer
	lda #MODE_SAVE
	jsr reu_copy
	stx address + 2
	lda #MODE_LOAD
	jsr reu_copy
	lda buffer
	beq @reu_size_loop; bank 0 not overwritten

@end:
	lda #1
	rts


ramlink_save:
	lda #$01
	jsr rl_setup
	lda #$00
	jsr reu_setup
@loop:
	print_progress message_read_rl
	jsr rl_copy
	print_progress message_write_reu
	jsr reu_copy
	jsr increase_address
	bne @loop
	print_string message_rl_saved
	rts

ramlink_restore:
	lda #$00
	jsr rl_setup
	lda #$01
	jsr reu_setup
@loop:
	print_progress message_read_reu
	jsr reu_copy
	print_progress message_write_rl
	jsr rl_copy
	jsr increase_address
	bne @loop
	print_string message_rl_restored
	rts

increase_address:
	cic
	lda address
	adc buffer_length
	sta address
	lda address + 1
	adc buffer_length + 1
	sta address + 1
	lda address + 2
	adc #$00
	sta address + 2

	lda address
	cmp end_address
	bne @end
	lda address + 1
	cmp end_address + 1
	bne @end
	lda address + 2
	cmp end_address + 2
@end:	rts

.data

message_read_reu:
	.byte "reading reu ", 0

message_write_reu:
	.byte "writing reu ", 0

message_read_rl:
	.byte "reading rl  ", 0

message_write_rl:
	.byte "writing rl  ", 0

message_rl_saved:
	.byte "ramlink backed up", 0

message_rl_restored:
	.byte "ramlink restored", 0

.bss
address:
	.byte 0, 0, 0

length:
	.byte 0, 0

end_address:
	.byte 0, 0, 0

mode:
	.byte 0

.code
rl_copy:
	sta mode
	jsr EN_SET_REC
	lda mode
	sta RL_REG_COMMAND
	lda #<buffer
	sta RL_REG_COMPUTER
	lda #>buffer
	sta RL_REG_COMPUTER + 1
	lda address
	sta RL_REG_RAMLINK
	lda address + 1
	sta RL_REG_RAMLINK + 1
	lda address + 2
	sta RL_REG_RAMLINK + 2
	lda #<buffer_length
	sta RL_TRANSFER_LENGTH
	lda #>buffer_length
	sta RL_TRANSFER_LENGTH + 1
	lda #$00
	sta RL_ADDR_CONTROL
	jmp RL_RW_DIS

reu_setup:
	sta mode
	lda #<buffer
	sta REU_REG_COMPUTER
	lda #>buffer
	sta REU_REG_COMPUTER + 1
	lda address
	sta REU_REG_RAMLINK
	lda address + 1
	sta REU_REG_RAMLINK + 1
	lda address + 2
	sta REU_REG_RAMLINK + 2
	lda #<buffer_length
	sta REU_TRANSFER_LENGTH
	lda #>buffer_length
	sta REU_TRANSFER_LENGTH + 1
	lda #$00
	sta REU_ADDR_CONTROL
	lda mode
	ora #$90
	sta REU_REG_CONTROL
	rts
