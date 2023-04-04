
CFLAGS=-g -Wall -Wextra -Werror -fsanitize=address
PROGS=xort

all: $(PROGS)

test-%: xort
	./test.sh $*

clean:
	rm -f $(PROGS)

