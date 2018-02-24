#
# I³C Runtime Environment
#
# Makefile


#PROGRAMMER = avrisp2
#PROGRAMMER = usbasp
#PROGRAMMER = usbtiny
PROGRAMMER = linuxspi
PORT = /dev/spidev0.0
CPU_GCC = attiny44
CPU_DUDE = t44

F_CPU = 8000000


CDEFS = -DF_CPU=$(F_CPU)
CFLAGS = -mmcu=$(CPU_GCC) $(CDEFS) -Wall -Os \
  -Wl,--section-start=.text=0x200 \
  -Wl,--section-start=.data=0x80007F \
  -Wl,--section-start=.bootreset=0x00
# TODO try to get the addresses from the header file

PROGRAM = i3c_runtime

.phony: clean

all: $(PROGRAM).hex

program: $(PROGRAM).hex
	echo 25 > /sys/class/gpio/export
	avrdude -c $(PROGRAMMER) -P $(PORT) -p $(CPU_DUDE) -U flash:w:$(PROGRAM).hex
	
fuse:
	echo 25 > /sys/class/gpio/export
	avrdude -c $(PROGRAMMER) -P $(PORT) -p $(CPU_DUDE) -U lfuse:w:0xc2:m -U hfuse:w:0xdd:m -U efuse:w:0xfe:m 

readout:
	echo 25 > /sys/class/gpio/export
	avrdude -c $(PROGRAMMER) -P $(PORT) -p $(CPU_DUDE) -U flash:r:flash_content.hex:i

clean:
	rm *.o *.elf *.hex

$(PROGRAM).hex: $(PROGRAM).c $(PROGRAM).h
	avr-gcc $(CFLAGS) -c usitwislave/usitwislave.c -o usitwislave.o
	avr-gcc $(CFLAGS) -c $(PROGRAM).c  -o $(PROGRAM).o -Iusitwislave
	avr-gcc $(CFLAGS) $(PROGRAM).o usitwislave.o -o $(PROGRAM).elf
#	avr-gcc $(CFLAGS) $(PROGRAM).o -o $(PROGRAM).elf
	avr-objcopy -R .eeprom -O ihex $(PROGRAM).elf $(PROGRAM).hex
	avr-nm --size-sort --print-size -r -td $(PROGRAM).elf
	avr-size $(PROGRAM).elf


