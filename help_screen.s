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
    scrcode "Tachyon RL - Back up RAMLink to Ultimate"
    scrcode "                                        "
    scrcode "Tachyon RL uses your 1541 Ultimate or   "
    scrcode "Ultimate II+ cartridge to back up and   "
    scrcode "restore your CMD RAMLink.               "
    scrcode "                                        "
    scrcode "* Put the Ultimate in the Pass Through  "
    scrcode "  port of your RAMLink.                 "
    scrcode "* Enable both Command Interface and RAM "
    scrcode "  Expansion Unit (REU) on the Ultimate. "
    scrcode "* Load and start Tachyon RL.            "
    scrcode "* Select backup or restore.             "
    scrcode "* Enter the name of your backup file.   "
    scrcode "  This is relative to your home         "
    scrcode "  directory (or / if not set). Full path"
    scrcode "  always works (e. g. /Usb0/backups/rl)."
    scrcode "                                        "
    scrcode "Estimated time for backup or restore:   "
    scrcode "+--------------+-----------+----------+ "
    scrcode "| RAMLink Size |    C64    | SuperCPU | "
    scrcode "|     4 MB     | ca. 2 min | ca. 15 s | "
    scrcode "|    16 MB     | ca. 8 min | ca. 90 s | "
    scrcode "+--------------+-----------+----------+ "
    scrcode "                                        "
    scrcode "                  (C) 2020 Dillo / T'Pau"
