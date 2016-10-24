#
# Makefile para EP4
#

CFLAGS = -ansi -Wall -pedantic -O2


.PHONY: clean


all: ep4


ep4: tabelaSimbolo.o buffer.o tabelaSimbolo_VO.o tabelaSimbolo_VD.o arrayOps.o
	$(CC) -o $@ $^
	rm -f *.o *~


%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f *.o *~ ep4
