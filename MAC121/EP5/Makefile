#
# Makefile para EP5
#

CFLAGS = -ansi -Wall -pedantic -O2


.PHONY: clean


all: ep5


ep5: hex.o hexBoard.o game.o pathFind.o hexAI.o hashTable.o hexAI_alphaBeta.o error.o
	$(CC) -o $@ $^


%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f *.o *~ ep5
