PROJECT	= project2
HEADERS	= $(PROJECT).h 
OBJ	= project2.o lattice.o scatter.o stack.o level_process.o perco_search.o

C99	= mpicc -std=c99
CFLAGS	= -Wall -pedantic -Werror -fopenmp

$(PROJECT) : $(OBJ)
	$(C99) $(CFLAGS) -o $(PROJECT) $(OBJ)

%.o : %.c $(HEADERS)
	$(C99) $(CFLAGS) -c $<

clean:
	rm -f $(PROJECT) $(OBJ) 
