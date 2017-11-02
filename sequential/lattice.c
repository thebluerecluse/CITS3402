/*  Zhiwei Huang    21450851        
    Ken Di Vincenzo 21946068
*/

#include "percolation.h"

// Functions for initialising, populating and freeing lattice

int** generate_lattice(int m, int n)
{
        int **lattice = calloc(m , sizeof(int*));
        for (int i = 0 ; i < m ; i++)
        {
                lattice[i] = calloc(n , sizeof(int));
        }
        return lattice;
}

void fill_site_lattice (int **lattice, int m, int n, double p)
{
        srand(time(NULL));
        double r = 0.0;
        for (int i = 0 ; i < m ; i++)
        {
                for (int j = 0 ; j < n ; j++)
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

                        int first = -1;
                        int count = 0;

                        bond_id = cell_transition(i, j);
                        neighbours = get_neighbours(bond_id, N, N);

                        while (count < 2) {

                                r = (double)rand()/(double)RAND_MAX;
                                if (r < p) {

                                        which = (double)rand()/(double)RAND_MAX * 4;
                                        if (which >= 0 && which < 1 && first != 1) {

                                                bond_partner = neighbours.north;
                                                if (is_bonded(bond_id, bond_partner, 0) == 1) {
                                                        continue;
                                                } else {
                                                        partner_x = bond_partner/N;
                                                        partner_y = bond_partner%N;
                                                        lattice[i][j] = lattice[i][j] + 8;
                                                        lattice[partner_x][partner_y] = lattice[partner_x][partner_y] + 2;
        
                                                        first = 1;
                                                        count++;   
                                                }

                                        } else if (which >= 1 && which < 2 && first != 2) {

                                                bond_partner = neighbours.east;
                                                if (is_bonded(bond_id, bond_partner, 1) == 1) {
                                                        continue;
                                                } else {
                                                        partner_x = bond_partner/N;
                                                        partner_y = bond_partner%N;
                                                        lattice[i][j] = lattice[i][j] + 4;
                                                        lattice[partner_x][partner_y] = lattice[partner_x][partner_y] + 1;

                                                        first = 2;
                                                        count++;
                                                }

                                        } else if (which >= 2 && which < 3 && first != 3) {

                                                bond_partner = neighbours.south;
                                                if (is_bonded(bond_id, bond_partner, 2) == 1) {
                                                        continue;
                                                } else {
                                                        partner_x = bond_partner/N;
                                                        partner_y = bond_partner%N;
                                                        lattice[i][j] = lattice[i][j] + 2;
                                                        lattice[partner_x][partner_y] = lattice[partner_x][partner_y] + 8;

                                                        first = 3;
                                                        count++;
                                                }

                                        } else {

                                                bond_partner = neighbours.west;
                                                if (is_bonded(bond_id, bond_partner, 3) == 1) {
                                                        continue;
                                                } else {
                                                        partner_x = bond_partner/N;
                                                        partner_y = bond_partner%N;
                                                        lattice[i][j] = lattice[i][j] + 1;
                                                        lattice[partner_x][partner_y] = lattice[partner_x][partner_y] + 4;
                                                        
                                                        first = 4;
                                                        count++;
                                                } 

                                        }
                                }
                        }
                }
        }
}

void free_lattice (int **lattice, int col_depth)
{
        for (int i = 0 ; i < col_depth ; i++) {
                free(lattice[i]);
        }
        free(lattice);
}