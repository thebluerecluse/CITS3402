PROJECT	= percolation
HEADERS	= $(PROJECT).h 
OBJ	= stack.o percolation.o lattice.o DFS_site.o DFS_bond.o

C99	= cc -std=c99
CFLAGS	= -Wall -pedantic -Werror

$(PROJECT) : $(OBJ)
	$(C99) $(CFLAGS) -o $(PROJECT) $(OBJ)

%.o : %.c $(HEADERS)
	$(C99) $(CFLAGS) -c $<

clean:
	rm -f $(PROJECT) $(OBJ) 
