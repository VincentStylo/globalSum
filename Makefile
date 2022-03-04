CFLAGS = -g -Wall -Wstrict-prototypes
PROGS = driver
OBJECTS = gsum.o function.o
LDFLAGS = -lm
CC = gcc
MCC = pmicc

all: $(PROGS)

driver: $(OBJECTS)
	$(MCC) $(LDFLAGS) -o driver $(OBJECTS)

gsum.o: gsum.c
	$(MCC) $(CFLAGS) -c gsum.c

function.o: fusnction.c function.h
	$(MCC) $(CFLAGS) ic funciton.c

clean:
	rm -f $(PROGS) *.o core* 
