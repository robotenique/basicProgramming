#
# Makefile para Parte 1 do projeto.
#

CFLAGS = -ansi -Wall -pedantic -O2


.PHONY: clean


all: ep4


ep4: freqT.o buffer.o
	$(CC) -o $@ $^


%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f *.o *~ ep4
