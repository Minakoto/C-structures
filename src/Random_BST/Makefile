CC = g++

all: build

build: menu test

menu: menu.o
	$(CC) menu.o -o menu
	rm *.o

menu.o: menu.cpp rnd_btree.h
	$(CC) -c menu.cpp

test: test.o
	$(CC) test.o -o test
	rm *.o

test.o: test.cpp rnd_btree.h
	$(CC) -c test.cpp

clean:
	rm menu test
