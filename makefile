CC = gcc

CFLAGS = -std=c99 -pedantic -Wall -c -Iinclude

all:
	make build
	
main.o:
	$(CC) $(CFLAGS) src/main.c -o bin/main.o
	
testmain.o:
	$(CC) $(CFLAGS) src/testmain.c -o bin/testmain.o	


BinarySearchTreeAPI.o:
	$(CC) $(CFLAGS) src/BinarySearchTreeAPI.c -o bin/BinarySearchTreeAPI.o		

Assistant.o:
	$(CC) $(CFLAGS) src/Assistant.c -o bin/Assistant.o

build:  main.o BinarySearchTreeAPI.o Assistant.o testmain.o
	$(CC) bin/main.o bin/BinarySearchTreeAPI.o bin/Assistant.o -Iinclude -o bin/runMe
	$(CC) bin/testmain.o bin/BinarySearchTreeAPI.o bin/Assistant.o -Iinclude -o bin/testMe   

run:
	./bin/runMe
clean:
	rm bin/*.o
	
