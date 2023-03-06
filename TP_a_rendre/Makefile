
CFLAGS = -Wall -Wextra -Werror

PROG = exdir # seul programme dans ce répertoire

all: $(PROG)

exdir: exdir.c # pas de fichier .o intermédiaire

test: exdir
	./test.sh

clean:
	rm -f $(PROG) test.log

