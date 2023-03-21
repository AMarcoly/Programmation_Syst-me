all : pip_a pip_b pip_c pip_red1a pip_red1b pip_red1c pip_red2 
CC = gcc -g
CFLAGS = -Wall -Wextra
LDFLAGS = -lm
SOURCES = $(wildcard *.c)
OBJETS = $(SOURCES:.c=.o)

pip_a : pip_a.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -r *.o

pip_b : pip_b.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -r *.o

pip_c : pip_c.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -r *.o

pip_red1a : pip_red1a.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -r *.o
pip_red1b : pip_red1b.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -r *.o
pip_red1c : pip_red1c.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -r *.o

pip_red2 : pip_red2.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -r *.o

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean : 
	rm -r *.o


cleanExec :
	rm pip_a
	rm pip_b
	rm pip_c
	rm pip_red1a
	rm pip_red1b
	rm pip_red1c
	rm pip_red2

cleantxt :
	rm *.txt

doc :
	doxygen doxyfile