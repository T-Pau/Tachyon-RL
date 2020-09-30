;  help_screen.s -- Help screen text.
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

.export        _help_screen
.macpack cbm

; extern const char *help_screen;

.segment    "RODATA"

_help_screen:
    .word L1

L1:
    scrcode "Backup/restore with Ultimate cartridge: "
    scrcode "                                        "
    scrcode "* On the Ultimate in C64 and Cartridge  "
    scrcode "  Settings disable Alternate Kernal and "
    scrcode "  enable Command Interface and REU.     "
    scrcode "* Select NORMAL on the lower switch of  "
    scrcode "  your RAMLink and put the Ultimate in  "
    scrcode "  the Pass-Thru port.                   "
    scrcode "* If you have a SuperCPU, turn Turbo on."
    scrcode "* Load and start Tachyon RL.            "
    scrcode "* Select backup or restore.             "
    scrcode "* Enter the name of your backup file.   "
    scrcode "  This is relative to your home         "
    scrcode "  directory (or / if not set). Full path"
    scrcode "  always works (e. g. /Usb0/backups/rl)."
    scrcode "                                        "
    scrcode "Approximate time for backup or restore: "
    .byte $20, $70, $40, $40, $40, $40, $40, $72, $40, $40
    .byte $40, $40, $40, $72, $40, $40, $40, $40, $40, $40
    .byte $40, $40, $40, $40, $40, $72, $40, $40, $40, $40
    .byte $40, $40, $40, $40, $40, $40, $40, $6e, $20, $20
    scrcode " |Size | C64 |SuperCPU V1|SuperCPU V2|  "
    scrcode " | 4 MB|2 min|    18 s   |    14 s   |  "
    scrcode " |16 MB|7 min|    72 s   |    55 s   |  "
    .byte $20, $6d, $40, $40, $40, $40, $40, $71, $40, $40
    .byte $40, $40, $40, $71, $40, $40, $40, $40, $40, $40
    .byte $40, $40, $40, $40, $40, $71, $40, $40, $40, $40
    .byte $40, $40, $40, $40, $40, $40, $40, $7d, $20, $20
    scrcode "                  (C) 2020 Dillo / T'Pau"

    scrcode "Backup/restore with SD2IEC:             "
    scrcode "                                        "
    scrcode "* Connect your SD2IEC.                  "
    scrcode "                                        "
    scrcode "* If you have a SuperCPU, turn Turbo on."
    scrcode "                                        "
    scrcode "* Load and start Tachyon RL.            "
    scrcode "                                        "
    scrcode "* Select backup or restore.             "
    scrcode "                                        "
    scrcode "* Enter the name of your backup file.   "
    scrcode "                                        "
    scrcode "                                        "
    scrcode "                                        "
    scrcode "Approximate time for backup or restore: "
    .byte $20, $70, $40, $40, $40, $40, $40, $72, $40, $40
    .byte $40, $40, $40, $40, $72, $40, $40, $40, $40, $40
    .byte $40, $40, $40, $40, $40, $40, $72, $40, $40, $40
    .byte $40, $40, $40, $40, $40, $40, $40, $40, $6e, $20
    scrcode " |Size | C64  |SuperCPU V1|SuperCPU V2| "
    scrcode " | 4 MB|18 min|   15 min  |   15 min  | "
    scrcode " |16 MB|72 min|   60 min  |   60 min  | "
    .byte $20, $6d, $40, $40, $40, $40, $40, $71, $40, $40
    .byte $40, $40, $40, $40, $71, $40, $40, $40, $40, $40
    .byte $40, $40, $40, $40, $40, $40, $71, $40, $40, $40
    .byte $40, $40, $40, $40, $40, $40, $40, $40, $7d, $20
    scrcode "                                        "
    scrcode "                                        "
    scrcode "                  (C) 2020 Dillo / T'Pau"
