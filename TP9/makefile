all : ecoute_active ecoute_passive attente compteur masque
CC = gcc -g
CFLAGS = -Wall -Wextra
LDFLAGS = -lm
SOURCES = $(wildcard *.c)
OBJETS = $(SOURCES:.c=.o)

ecoute_active : ecoute_active.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -r *.o

ecoute_passive: ecoute_passive.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -r *.o

attente: attente.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -r *.o
	
compteur: compteur.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -r *.o

masque: masque.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -r *.o

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm ecoute_active
	rm ecoute_passive
	rm attente
	rm compteur
	rm masque

cleantxt :
	rm *.txt

doc :
	doxygen doxyfile