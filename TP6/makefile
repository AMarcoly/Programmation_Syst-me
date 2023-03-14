all : pip_a pip_b pip_c pip_red1 pip_red2 pip_red3
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

pip_red1 : pip_red1.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -r *.o
pip_red2 : pip_red2
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -r *.o
pip_red3 : pip_red3
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
	rm pip_red1
	rm pip_red2
	rm pip_red3

cleantxt :
	rm *.txt

doc :
	doxygen doxyfile