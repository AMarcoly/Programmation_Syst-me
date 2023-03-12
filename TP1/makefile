all : cp_sys cp_std cp_rev read_int write_int
CC = gcc -g
CFLAGS = -Wall -Wextra
LDFLAGS = -lm
SOURCES = $(wildcard *.c)
OBJETS = $(SOURCES:.c=.o)


cp_sys : cp_sys.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -r *.o

cp_std : cp_std.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -r *.o

cp_rev : cp_rev.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -r *.o

read_int:read_int.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -r *.o

write_int: write_int.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -r *.o

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean : 
	rm -r *.o

cleanExec :
	rm cp_sys
	rm cp_std
	rm cp_rev
	rm read_int
	rm write_int

cleantxt :
	rm *.txt

doc :
	doxygen doxyfile