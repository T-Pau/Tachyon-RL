; based on Providing Multiple Drive Support via Machine Language
;   https://codebase64.org/doku.php?id=base:detect_drives_on_iec_bus
;
; polls all available drives
; By Todd S. Elliott
; Buddy assembler format
; Feel free to use the routine without any attribution.

; Adapted for cc65 by Dieter Baron.

.export _drive_types, _detect_drives
.importzp tmp1

.include "cbm_kernal.inc"
.include "c64.inc"

.macro send_command addr
    lda #15
    tay
    ldx DEVNUM
    jsr SETLFS ; 15,DEVNUM,15
    lda #$07; length of m-r command
    ldx #<addr
    ldy #>addr
    jsr SETNAM
    jsr OPEN
    ldx #15
    jsr CHKIN
.endmacro

DRIVE_TYPE_NONE = 0
DRIVE_TYPE_UNKNOWN = 1
DRIVE_TYPE_1541 = 2
DRIVE_TYPE_1571 = 3
DRIVE_TYPE_1581 = 4
DRIVE_TYPE_CMD_FD = 5
DRIVE_TYPE_CMD_HD = 6
DRIVE_TYPE_RAMDRIVE = 7
DRIVE_TYPE_RAMLINK = 8

MAX_DEVICE = 30

STATUS = $90

.segment "BSS"

; extern unsigned char drive_types[32];

_drive_types:
    .res 32

.segment "RODATA"

info_cmd:
    .byte "m-r", $a4, $fe, $02, $0d

info_cbm:
    .byte "m-r", $c5, $e5, $02, $0d

info_1581:
    .byte "m-r", $e8, $a6, $02, $0d

.segment "CODE"

; void __near__ detect_drives(void);

    .proc _detect_drives: near

.segment    "CODE"

    ; initialize drive types with NONE
    ldy #31
    lda #0
init_loop:
    sta _drive_types,y
    dey
    bpl init_loop

    ; remember current drive
    lda DEVNUM
    sta tmp1

    lda #8
    sta DEVNUM
detect_drive:
    ldy #$00
    sty STATUS
    jsr LISTEN
    lda #$ff ; open channel 15
    jsr SECOND
    lda STATUS
    bpl device_found
    jsr UNLSN

; The following sub-routine was 'commented' by the semi-colon. Either way,
; the drive polling with or without the commented sub-routine will work
; correctly. The reason why I left it there is because Commodore World #10-11
; articles on serial bus routines recommended such an anal-retentive
; sequence. I'm sure it is for a good reason though. If you can spare the
; room, feel free to use the commented routine by removing the semi-colons.

; lda #$00
; sta STATUS; clear the status register
; lda DEVUNM; get device number
; jsr LISTEN; opens the device for listening
; lda #$ef; sa - $0f and OR'ed with $e0 to close file
; jsr SECOND; closes the channel with sa of 15
; jsr UNSN; finally closes it

detect_drive_next:
    inc DEVNUM
    lda DEVNUM
    cmp #(MAX_DEVICE + 1)
    bne detect_drive
    beq detect_types

device_found:
    ldy DEVNUM
    tya
    sta _drive_types,y
    bne detect_drive_next

detect_types:
    ldy #8
detect_types_loop:
    lda _drive_types,y
    bne detect_type
    iny
    cpy #(MAX_DEVICE + 1)
    bne detect_types_loop

    ; all done, restore drive number
    lda tmp1
    sta DEVNUM
    rts

detect_type:
    sta DEVNUM
    send_command info_cmd

    jsr CHRIN
    cmp #70; is it 'f' for FD series drives?
    bne not_cmd_fd
    jsr CHRIN; get next character
    cmp #68; is it 'd' for FD series drives?
    bne detect_cbm
    lda #DRIVE_TYPE_CMD_FD
    jmp get_next_drive

not_cmd_fd:
    cmp #72; is it 'h' for HD series drives?
    bne not_cmd_hd
    jsr CHRIN
    cmp #68; is it 'd' for HD series drives?
    bne detect_cbm
    lda #DRIVE_TYPE_CMD_HD
    bne get_next_drive; relative JMP

not_cmd_hd:
    cmp #82; is it 'r' for RL/RD series?
    bne detect_cbm
    jsr CHRIN
    cmp #68; is it 'd' for RD series?
    bne not_cmd_rd
    lda #DRIVE_TYPE_RAMDRIVE
    bne get_next_drive; relative JMP
not_cmd_rd:
    cmp #76; is it 'l' for RL series?
    bne detect_cbm
    lda #DRIVE_TYPE_RAMLINK
    bne get_next_drive; relative JMP

detect_cbm:
    jsr close_command_channel
    send_command info_cbm

    jsr CHRIN; gets the drive info
    cmp #53; is it '5' for the 15xx drives?
    bne detect_1581
    jsr CHRIN; gets the next number
    cmp #52; is it '4' for the 1541?
    bne not_1541
    lda #DRIVE_TYPE_1541
    bne get_next_drive; relative JMP
not_1541:
    cmp #55; is it '7' for the 1571?
    bne detect_1581
    lda #DRIVE_TYPE_1571
    bne get_next_drive; relative JMP

detect_1581:
    jsr close_command_channel
    send_command info_1581

    jsr CHRIN
    cmp #53; '5'
    bne not_recognized
    jsr CHRIN
    cmp #56; '8'
    bne not_recognized
    lda #DRIVE_TYPE_1581
    bne get_next_drive; relative JMP

not_recognized:
    lda #DRIVE_TYPE_UNKNOWN

get_next_drive:
    ldy DEVNUM
    sta _drive_types,y
    jsr close_command_channel
    ldy DEVNUM
    iny
    jmp detect_types_loop

close_command_channel:
    jsr CLRCHN
    lda #15
    jmp CLOSE

.endproc
