/*  Zhiwei Huang    21450851        
    Ken Di Vincenzo 21946068
*/

#include "percolation.h"

// Functions for initialising, populating and freeing lattice

int** generate_lattice(int m, int n)
{
        int **lattice = calloc(m , sizeof(int*));
        for (int i = 0; i < m; i++)
        {
                lattice[i] = calloc(n , sizeof(int));
        }
        return lattice;
}

void fill_lattice (int **lattice, int m, int n, double p)
{
        srand(time(NULL));
        double r = 0.0;
        for (int i = 0; i < m; i++)
        {
                for (int j = 0; j < n; j++)
                {
                        r = (double)rand()/(double)RAND_MAX;
                        if (r < p)
                                lattice[i][j] = 1;
                }
        }
}

void free_lattice (int **lattice, int col_depth)
{
        for (int i = 0; i < col_depth; i++)
                free(lattice[i]);
        free(lattice);
}
