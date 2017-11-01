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

void fill_site_lattice (int **lattice, int m, int n, double p)
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

void fill_bond_lattice(int **lattice, int m, int n, double p)
{
        //using binary bits to indicate bond occupancy, 8421 bits = nesw ie 1010 indicates bonds to north and south
        srand(time(NULL));
        double r = 0.0;
        double which = 0.0;

        int bond_id;
        int bond_partner;
        int partner_x;
        int partner_y;
        struct Nbrs neighbours;

        for(int i = 0 ; i < m ; i++) {
                for(int j = 0 ; j < n ; j++) {
                        if (lattice[i][j] > 0) {
                                continue;
                        }
                        
                        r = (double)rand()/(double)RAND_MAX;
                        if (r < p) {
                                which = (double)rand()/(double)RAND_MAX * 4;
                                bond_id = cell_transition(i, j);
                                neighbours = get_neighbours(bond_lattice, bond_id, N, N);
                                if (which >= 0 && which < 1) {

                                        bond_partner = neighbours.north;
                                        partner_x = bond_partner/N;
                                        partner_y = bond_partner%N;
                                        lattice[i][j] = lattice[i][j] + 8;
                                        lattice[partner_x][partner_y] = lattice[partner_x][partner_y] + 2;

                                } else if (which >= 1 && which < 2) {

                                        bond_partner = neighbours.east;
                                        partner_x = bond_partner/N;
                                        partner_y = bond_partner%N;
                                        lattice[i][j] = lattice[i][j] + 4;
                                        lattice[partner_x][partner_y] = lattice[partner_x][partner_y] + 1;

                                } else if (which >= 2 && which < 3) {

                                        bond_partner = neighbours.south;
                                        partner_x = bond_partner/N;
                                        partner_y = bond_partner%N;
                                        lattice[i][j] = lattice[i][j] + 2;
                                        lattice[partner_x][partner_y] = lattice[partner_x][partner_y] + 8;

                                } else {

                                        bond_partner = neighbours.west;
                                        partner_x = bond_partner/N;
                                        partner_y = bond_partner%N;
                                        lattice[i][j] = lattice[i][j] + 1;
                                        lattice[partner_x][partner_y] = lattice[partner_x][partner_y] + 4;

                                }
                        }
                }
        }
}

void free_lattice (int **lattice, int col_depth)
{
        for (int i = 0; i < col_depth; i++)
                free(lattice[i]);
        free(lattice);
}