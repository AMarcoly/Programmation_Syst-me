all: fork1 fork2 fork3 run script
CC = gcc -g
CFLAGS = -Wall -Wextra
LDFLAGS = -lm

SOURCES = $(wildcard *.c)
OBJETS = $(SOURCES:.c=.o)

fork1: fork1.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) 
	rm -r *.o

fork2 : fork2.o 
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) 
	rm -r *.o

fork3 : fork3.o 
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) 
	rm -r *.o

run : run.o 
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) 
	rm -r *.o

script : script.o 
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) 
	rm -r *.o

%.o : %.c 
	$(CC) $(CFLAGS) -c $<


clean : 
	rm fork1
	rm fork2
	rm fork3
	rm run
	rm script
	rm toto
	rm sortie

cleantxt :
	rm *.txt

doc :
	doxygen doxyfile
