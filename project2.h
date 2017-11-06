#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>

#define N		1024	//lattice size base
#define SITE_R		N	//site lattice number of rows
#define SITE_C		N	//number of columns
#define BOND_R		2*N	//bond lattice is a merged lattice, number of rows is twice as number of columns
#define BOND_C		N	//bond lattice number of columns
#define NUM_THREADS 	1	//openmp number of threads
#define MASTER 		0	//mpi process master
#define SEND_DATA_TAG	2001	//mpi send tag
#define RECV_DATA_TAG	2002	//mpi receive tage
#define STACK_MAX	SITE_R * SITE_C

int *lattice;			//generated lattice
int *lattice_for_row;	//meant to be a transpose of lattice

//stack data structure
typedef struct Stack {
	int *data;
	int size;
} Stack;

//lattice.c
//lattice generation, filling, printing
extern void generate_lattice(char );
extern void	fill_lattice(double, char );
extern void	print_lattice(char );
extern void	print_row_lattice(char );
extern void	transpose_lattice(char );
//scatter.c
//find out the length of lattice size for MASTER process to send
extern int	send_length(int, char );
//level_process.c
//process each row of lattice, for every connected nodes on the same row
//will be connected and record the size of such "row cluster" on each site
extern int *	level_process(int , int *, char );
//stack.c
extern void	Stack_Init(Stack * );
extern int	Stack_Top(Stack * );
extern void	Stack_Push(Stack * , int );
extern void	Stack_Pop(Stack *);
//perco_search.c
//after obtaining the processed lattice which has "row cluster"
//connect each row from up to down and update the size as the percolation
//goes down, each row's size is the previous ones sum and itself
extern void	perco_search(int * , int * , int *, char );
