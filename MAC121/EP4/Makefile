#
# Makefile para EP4
#

CFLAGS = -ansi -Wall -pedantic -O2


.PHONY: clean


all: ep4


ep4: tabelaSimbolo.o buffer.o arrayOps.o tabelaSimbolo_VO.o tabelaSimbolo_VD.o tabelaSimbolo_LO.o tabelaSimbolo_LD.o tabelaSimbolo_AB.o frequenciaCalc.o
	$(CC) -o $@ $^


%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f *.o *~ ep4
