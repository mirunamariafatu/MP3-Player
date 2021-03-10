# Copyright 2019 Darius Neatu <neatudarius@gmail.com>

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -g -std=gnu11

# define targets
TARGETS=tema1

build: $(TARGETS)

tema1:main.o  tema1.o
	$(CC) $(CFLAGS) main.o tema1.o -o tema1

tema1.o: tema1.c
	$(CC) $(CFLAGS) tema1.c -c -o tema1.o

main.o: main.c
	$(CC) $(CFLAGS) main.c -c -o main.o

pack:
	zip -FSr 311CA_MirunaMariaFatu_Tema1.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)
