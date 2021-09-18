all: exec
exec: cards
	gcc botenildson.c cards.o -o ../bin/botenildson
cards: cards.c
	gcc cards.c -c
clean:
	rm -rf *.o
