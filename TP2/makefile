all : my_stat ls1 ls2 ls_rec chercher_chaine
CC = gcc -g
CFLAGS = -Wall -Wextra
LDFLAGS = -lm
SOURCES = $(wildcard *.c)
OBJETS = $(SOURCES:.c=.o)



my_stat : my_stat.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -r *.o

ls1 : ls1.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -r *.o

ls2 : ls2.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -r *.o

ls_rec:ls_rec.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -r *.o

chercher_chaine: chercher_chaine.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -r *.o

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean : 
	rm -r *.o

cleanExec :
	rm my_stat
	rm ls1
	rm ls2
	rm ls_rec
	rm chercher_chaine

cleantxt :
	rm *.txt

doc :
	doxygen doxyfile