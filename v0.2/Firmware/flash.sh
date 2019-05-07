#! /bin/bash
cd $1
esptool.py --port /dev/ttyUSB0 write_flash -fm qio 0x00000 $1.ino.nodemcu.bin

