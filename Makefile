CFLAGS = -g -Wall -Wstrict-prototypes
PROGS = driver
OBJECTS = gsum.o function.o
LDFLAGS = -lm
CC = gcc
MCC = mpicc

all: $(PROGS)

driver: $(OBJECTS)
	$(MCC) $(LDFLAGS) -o driver $(OBJECTS)

gsum.o: gsum.c
	$(MCC) $(CFLAGS) -c gsum.c

function.o: function.c function.h
	$(MCC) $(CFLAGS) -c function.c

clean:
	rm -f $(PROGS) *.o core* 
clean-windows:
	del -f $(PROGS) *.o core* 
