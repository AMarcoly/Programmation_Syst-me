
CFLAGS=-Wall -Wextra
# -g -fsanitize=address

PROGS=fltr

all: $(PROGS)

.PHONY: clean
clean:
	rm -f $(PROGS)


test-%: fltr
	./test.sh $*
