# Tachyon RL
## Back up RAMLink to Ultimate Cartridge

This program allows you to back up CMD RAMLink to a 1541 Ultimate or Ultimate II+ cartridge. It is much faster than backing up to floppies or SD2IEC, since it does not use the slow serial bus. It is even faster with CMD SuperCPU.

Approximate time for backup or restore:
|  RAMLink Size | C64 | SuperCPU |
|:-:|:-:|:-:|
| 4 MB | ca. 2 min | ca. 15 s |
| 16MB | ca. 8 min | ca. 90 s|

## Using

- Make sure your RAMLink is connected and enabled.
- If your RAMLink is not initialized, the detection code will hang. In that case, type `LOAD"$",16` to initialize it.
- Make sure your Ultimate cartridge is connected to the Pass-Thru port of your RAMLink.
- Enable Command Interface on Ultimate: Press Menu button, then `F2` and enable `Command Interface`.
- It will run much faster if you also enable the RAM Expansion Unit on Ultimate: Press Menu button, then `F2` and enable `RAM Expansion Unit`. A `REU Size` of 16MB is best.

## Building

You will need cc65 and the c5141 utility from Vice.

Type `make` to build a D64 image and a PRG file of Tachyon RL.
