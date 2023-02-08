#PHONY: all clean doc archive archiveclean

S_REP = src/
H_REP = include/
O_REP = obj/
B_REP = bin/
D_REP = doc/
CC = gcc

EXE = $(B_REP)cp_rev
SRC = $(wildcard $(S_REP)*.c)
OBJ = $(SRC:$(S_REP)%.c=$(O_REP)%.o)
RM 	= rm
CFLAGS := -Wall -Wextra \
		 -Wdouble-promotion -Wformat=2 -Winit-self -Wswitch-default \
		-Wswitch-enum -Wunused-parameter -Wuninitialized -Wfloat-equal	
LDLIBS = -lm

$(EXE) : $(OBJ) | $(B_REP)
	$(CC)  $^ $(LDLIBS) -o $@ $(LDFLAGS)

$(O_REP)%.o : $(S_REP)%.c | $(O_REP)
	$(CC) -c $< -o $@

$(B_REP) $(O_REP):
	mkdir $@

doc :
	doxygen Doxyfile

clean :
	$(RM) -r $(O_REP) $(B_REP) 
# $(D_REP)

# Archive
archive:
	tar -czf ANTOINE_Marcoly.tar.gz $(S_REP) $(H_REP) makefile *.md Doxyfile

#Suppression de l'archive
archiveclean:
	$(RM) *.tar.gz

