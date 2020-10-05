#!/bin/bash
avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"main.d" -MT"main.d" -c -o "main.o" "../main.c"
avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"servos.d" -MT"servos.d" -c -o "servos.o" "../servos.c"
avr-gcc -Wl,-Map,avrservo.map -mmcu=atmega328p -o "avrservo.elf"  ./main.o ./servos.o  
avr-objdump -h -S avrservo.elf  >"avrservo.lss"
avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex avrservo.elf  "avrservo.hex"
avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex avrservo.elf  "avrservo.eep"
avr-size --format=avr --mcu=atmega328p avrservo.elf