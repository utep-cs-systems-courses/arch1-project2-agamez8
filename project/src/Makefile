# makefile configuration
COMMON_OBJECTS	=
CPU		= msp430g2553
CFLAGS		= -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

# switch the compiler (for the internal make rules)
CC		= msp430-elf-gcc
AS		= msp430-elf-as

all: main.elf

#additional rules for files
main.elf: ${COMMON_OBJECTS} buzzer.o led.o switches.o stateMachines.o main.o 2p-interrupt.o wdInterruptHandler.o ../lib/libTimer.a 
	${CC} ${CFLAGS} ${LDFLAGS}  -o $@ $^

load: main.elf
	msp430loader.sh main.elf

clean:
	rm -f *.o *.elf *.c~ *.h~ *.c#

led.o: led.h

switches.o: switches.h led.h

buzzer.o: buzzer.h

stateMachines.o: stateMachines.h led.h buzzer.h

2p-interrupt.o: switches.h

wdInterruptHandler.o: led.h switches.h stateMachines.h buzzer.h

main.o: led.h switches.h buzzer.h
