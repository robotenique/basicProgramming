#
# Makefile para Parte 1 do projeto.
#

CFLAGS = -std=c99 -Wall -pedantic -O2


.PHONY: clean


all: sortT


sortT: sortingTest.o sort.o
	$(CC) -o $@ $^


%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f *.o *~ sortT
