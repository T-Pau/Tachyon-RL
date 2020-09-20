# Tachyon RL
## RAMLink Backup

This program allows you to back up CMD RAMLink to an Ultimate cartridge (1541 or II+) or SD2IEC. 

Using an Ultimate is fast, since it does not use the slow serial bus. SD2IEC is not as fast, but still more convenient and reliable than a stack of floppies.

CMD SuperCPU provides an additional speed boost.

Approximate time for backup or restore for 16 MB RAMLink (proportionally shorter for smaller size):

| Method | C64 | C128 | SuperCPU V1 | SuperCPU V2 |
|:-:|:-:|:-:|:-:|:-:|
| Ultimate with REU | 8 min | | 80 s | 60 s |
| Ultimate without REU| | | | |
| SD2IEC | | | 1 hour | |

## Using

- Make sure your RAMLink is connected and enabled.
- If you have a SuperCPU, set the `Speed` switch to `Turbo`.
- Make sure your Ultimate cartridge is connected to the Pass-Thru port of your RAMLink and the lower switch is set to `normal` (not `direct`).
- Enable Command Interface on Ultimate: Press Menu button, then `F2`, go to `C64 and Cartridge Settings` and enable `Command Interface`.
- It will run much faster if you also enable the RAM Expansion Unit on Ultimate: Press Menu button, then `F2`, go to `C64 and Cartridge Settings` and enable `RAM Expansion Unit`. A `REU Size` of 16MB is best.

## Building

You will need cc65 and the c1541 utility from Vice.

Type `make` to build a D64 image and a PRG file of Tachyon RL.
