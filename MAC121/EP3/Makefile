#
# Makefile para Parte 1 do projeto.
#

CFLAGS = -ansi -Wall -pedantic -O2


.PHONY: clean


all: ep3


ep3: tresReversao.o arrayOp.o
	$(CC) -o $@ $^


%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f *.o *~ ep3
