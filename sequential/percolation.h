/*  Zhiwei Huang    21450851        
    Ken Di Vincenzo 21946068
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
//#include <omp.h>

#define N 128		//size of square lattice, needs to be at least 3
#define STACK_MAX N*N

int **flag_lattice;
int **bond_lattice;
int **site_lattice;

// Declaration of structures to be used in the program

typedef struct Nbrs {
	int north;
	int south;
	int west;
	int east;
} Nbrs;

typedef struct Perc_size {
	int row;
	int col;
	int size;
} Perc_size;

typedef struct Cell {
	int x;
	int y;
} Cell;

typedef struct Stack {
    int     *data;
    int     size;
} Stack;

//stack function
extern void Stack_Init(Stack *);
extern int 	Stack_Top(Stack *);
extern void Stack_Push(Stack *, int );
extern void Stack_Pop(Stack *);

//generate lattice according to the command provided
//of site or bond
extern int** 			generate_lattice(int , int );
extern void 			fill_site_lattice(int **, int , int ,double );
extern void 			fill_bond_lattice(int **, int , int ,double );
extern void 			free_lattice(int **, int );
extern struct Nbrs 		get_neighbours(int , int , int );
extern int			    cell_transition(int , int );
extern struct Perc_size	DFS_site(int , int , int , int );
extern struct Perc_size	start_point(int , int , int **, char );
extern void 			percolate(int, char, int *, int *, double );
extern struct Perc_size DFS_bond(int , int , int , int );
extern int				is_bonded(int , int , int );