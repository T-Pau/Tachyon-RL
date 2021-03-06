# Tachyon RL
## RAMLink Backup

This program allows you to back up [CMD RAMLink](https://en.wikipedia.org/wiki/CMD_RAMLink) to an [Ultimate cartridge](https://ultimate64.com) (1541 or II+) or [SD2IEC](https://www.c64-wiki.com/wiki/SD2IEC) device. 

Using an Ultimate is fast, since it does not use the slow serial bus. SD2IEC is not as fast, but still more convenient and reliable than a stack of floppies.

[CMD SuperCPU](https://en.wikipedia.org/wiki/SuperCPU) provides an additional speed boost.

If you don't have any device supported by Tachyon but own a CMD HD, you can create a Foreign Mode (Direct Access) Partition with Foreign Creator and back up to it with BCopy+. Both programs are on the [CMD Utilities Disk](https://www.commodoreserver.com/PublicDiskDetails.asp?DID=5B0EEC90A196426FB209329067F756FD&SnapshotID=1).

Approximate time for backup or restore for 16 MB RAMLink (proportionally shorter for smaller size):

| Method | C64 | SuperCPU V1 | SuperCPU V2 |
|:-:|:-:|:-:|:-:|
| Ultimate | 7 min | 72 s | 55 s |
| SD2IEC | 72 min | 60 min | 60 min |

## Using

### Ultimate 

To back up or restore with an Ultimate cartridge, follow these steps:

- On the Ultimate, press the Menu button, then `F2`, go to `C64 and Cartridge Settings`. Disable `Alternate Kernal` (otherwise Ultimate and RAMLink are incompatible and will freeze). Enable `Command Interface` and `REU`. A `REU Size` of 16MB is recommended.
- If you have a SuperCPU, set the `Speed` switch to `Turbo`.
- Set the lower switch on your RAMLink to `normal` and the upper switch to `enabled`. Connect your Ultimate cartridge to the Pass-Thru port.
- Connect the RAMLink to your computer and turn it on.
- Load and start `Tachyon RL`.
- Select backup or restore.
- Enter the name of your backup file. This is relative to your home directory (or `/` if not set). A full path always works (e. g. `/Usb0/backups/rl`).

### SD2IEC

To back up or restore with an SD2IEC, follow these steps. Please note, backing up to an Ultimate cartridge is faster by a factor of 9 to 60, depending on CPU.

- Connect your SD2IEC to the serial port.
- Turn on your computer.
- Make sure no disk is mounted in SD2IEC. If it is, use `@CD←` to unmount. (Disk images usually aren't big enough to hold a RAMLink backup.)
- Load and start `Tachyon RL`.
- Select backup or restore.
- Enter the name of your backup file. This is relative to the current directory on your SD2IEC ( `/` by default). A full path always works (e. g. `//backups/rl`).

## Building

You will need [cc65](https://cc65.github.io), the `c1541` utility from [Vice](http://vice-emu.sourceforge.net), and Perl.

Type `make` to build a D64 image and a PRG file of Tachyon RL.
