/*  Zhiwei Huang    21450851        
    Ken Di Vincenzo 21946068
*/

#include "percolation.h"

int is_bonded(int ij, int xy, int direction)
{
	int i = ij / N;
	int j = ij % N;

	int x = xy / N;
	int y = xy % N;

	int node;
	int nbr;

	switch (direction) {
		//0 - north, 1 - east, 2 - south, 3 - west
		case 0:
			node = bond_lattice[i][j] & 8;
			nbr = bond_lattice[x][y] & 2;

			if (node == 8 && nbr == 2) {
				return 1;
			} else {
				return 0;
			}
		case 1:
			node = bond_lattice[i][j] & 4;
			nbr = bond_lattice[x][y] & 1;

			if (node == 4 && nbr == 1) {
				return 1;
			} else {
				return 0;
			}			
		case 2:
			node = bond_lattice[i][j] & 2;
			nbr = bond_lattice[x][y] & 8;

			if (node == 2 && nbr == 8) {
				return 1;
			} else {
				return 0;
			}	
		case 3:
			node = bond_lattice[i][j] & 1;
			nbr = bond_lattice[x][y] & 4;

			if (node == 1 && nbr == 4) {
				return 1;
			} else {
				return 0;
			}
		default:
			return 0;	
	}
}

struct Perc_size DFS_bond(int x, int y, int col_depth, int row_width)
{
        struct Nbrs neighbours; 	//Nbrs structure store the neighbours of current node
        struct Stack s;			//stack for DFS
        Stack_Init(&s);
	long long int xy;       	//single value record the neighboursition
	
	int *flag_row = calloc(col_depth , sizeof(int));
	int *flag_col = calloc(row_width , sizeof(int));

        int i = x;      	//row coordinate of a site
        int j = y;      	//column coordinate of a site
        int count = 0;  	//count the cluster size
        struct Perc_size pdfs; 	//be returned with percolated levels and size of cluster

        //perform dfs
        xy = cell_transition(x,y);
	flag_row[x] = 1;
	flag_col[y] = 1;
        Stack_Push(&s, xy);
        
        while (s.size > 0) {

                xy = Stack_Top(&s);
                Stack_Pop(&s);
                i = xy/row_width;
		j = xy%row_width;
		
                if (flag_lattice[i][j] != 1) {

                        flag_lattice[i][j] = 1;         //mark the node popped
                        neighbours = get_neighbours(bond_lattice, xy, col_depth, row_width);
			count++;
			
                        //north
                        if (neighbours.north > 0 && is_bonded(xy, neighbours.north, 0) == 1) {      	//if the site is seeded and not visited
                        
                                i = neighbours.north/row_width;
                                j = neighbours.north%row_width;
                                Stack_Push(&s, neighbours.north);      	//put the node in stack
                                flag_row[i] = 1;                        //record percolated level
                                flag_col[j] = 1;                        //record percolated level
			}
			
                        //south
                        if (neighbours.south > 0 && is_bonded(xy, neighbours.south, 2) == 1) {    	//if the site is seeded and not visited
                        
                                i = neighbours.south/row_width;
                                j = neighbours.south%row_width;
                                Stack_Push(&s, neighbours.south);
                                flag_row[i] = 1;
                                flag_col[j] = 1;
			}
			
                        //west
                        if (neighbours.west > 0 && is_bonded(xy, neighbours.west, 4) == 1) {           	//if the site is seeded and not visited
                        
                                i = neighbours.west/row_width;
                                j = neighbours.west%row_width;
                                Stack_Push(&s, neighbours.west);
                                flag_row[i] = 1;
                                flag_col[j] = 1;
			}
			
			//east
                        if (neighbours.east > 0 && is_bonded(xy, neighbours.east, 1) == 1) {      	//if the site is seeded and not visited

                                i = neighbours.east/row_width;
                                j = neighbours.east%row_width;
                                Stack_Push(&s, neighbours.east);
                                flag_row[i] = 1;
                                flag_col[j] = 1;
                        }
                }
        }
        
        pdfs.row = 1;
        pdfs.col = 1;
        for (int i = 0 ; i < col_depth ; i++)
        {
                if (flag_row[i] != 1)
		{
                        pdfs.row = 0;
			//break;
		}
        }
	free(flag_row);
        for (int j = 0 ; j < row_width ; j++)
        {
                if (flag_col[j] != 1)
		{
                        pdfs.col = 0;
			//break;
		}
        }
	free(flag_col);
        pdfs.size = count;
        return pdfs;
}



