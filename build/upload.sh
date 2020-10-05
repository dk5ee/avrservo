#!/bin/bash
avrdude -p m328p -b 57600 -c arduino -U flash:w:avrservo.elf :i -F -P /dev/ttyUSB3
