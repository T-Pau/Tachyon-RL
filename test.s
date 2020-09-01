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

buffer = $1000
buffer_length = $8000

ramlink_save:
	lda #$01
	jsr rl_setup
	lda #$00
	jsr reu_setup
.loop:
	print_progress(message_read_rl)
	jsr rl_copy
	print_progress(message_write_reu)
	jsr reu_copy
	jsr increase_address
	bne .loop
	print_string(message_rl_saved)
	rts

ramlink_restore:
	lda #$00
	jsr rl_setup
	lda #$01
	jsr reu_setup
.loop:
	print_progress(message_read_reu)
	jsr reu_copy
	print_progress(message_write_rl)
	jsr rl_copy
	jsr increase_address
	bne .loop
	print_string(message_rl_restored)
	rts

increase_address:
	clc
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
	bne +
	lda address + 1
	cmp end_address + 1
	bne +
	lda address + 2
	cmp end_address + 2
+	rts

message_read_reu
	.text "reading reu ", 0

message_write_reu
	.text "writing reu ", 0

message_read_rl:
	.text "reading rl  ", 0

message_write_rl:
	.text "writing rl  ", 0

message_rl_saved:
	.text "ramlink backed up", 0

message_rl_restored:
	.text "ramlink restored", 0

address:
	.bytes 0, 0, 0

end_address:
	.bytes 0, 0, 0

mode:
	.byte 0

rl_setup:
	sta mode
	jsr EN_SET_REC
	lda mode
	sta RL_REG_COMMAND
	lda #<buffer
	sta RL_REG_COMPUTER
	lda #>buffer
	sta RL_REG_COMPUTER + 1
	lda #$0
	sta RL_REG_RAMLINK
	sta RL_REG_RAMLINK + 1
	sta RL_REG_RAMLINK + 2
	lda #<buffer_length
	sta RL_TRANSFER_LENGTH
	lda #>buffer_length
	sta RL_TRANSFER_LENGTH + 1
	lda #$80
	sta RL_ADDR_CONTROL
	jmp RL_RW_DIS

rl_copy:
	jsr EN_SET_REC
	jmp EXEC_REU_DIS


reu_setup:
	ora #$80
	sta REU_REG_CONTROL
	lda #<buffer
	sta REU_REG_COMPUTER
	lda #>buffer
	sta REU_REG_COMPUTER + 1
	lda #$0
	sta REU_REG_RAMLINK
	sta REU_REG_RAMLINK + 1
	sta REU_REG_RAMLINK + 2
	lda #<buffer_length
	sta REU_TRANSFER_LENGTH
	lda #>buffer_length
	sta REU_TRANSFER_LENGTH + 1
	lda #$80
	sta REU_ADDR_CONTROL
	rts

reu_copy:
	lda #$00
	sta $ff00
	rts
