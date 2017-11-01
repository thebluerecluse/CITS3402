/*  Zhiwei Huang    21450851        
    Ken Di Vincenzo 21946068
*/

#include "percolation.h"

struct perc_size DFS_bond(int x, int y, int col_depth, int row_width)
{
        struct Nbrs neighbours; 	//neighbours structure store the neighbours of current node
        struct Stack s;		//stack for DFS
        Stack_Init(&s);
	long long int xy;       //single value record the neighboursition
	
	int *flag_row = calloc(col_depth , sizeof(int));
	int *flag_col = calloc(row_width , sizeof(int));

        int i = x;      	//row coordinate of a site
        int j = y;      	//column coordinate of a site
        int count = 0;  	//count the cluster size
        struct perc_size pdfs; 	//be returned with percolated levels and size of cluster

        //perform dfs
        xy = cell_transition(x,y);
	flag_row[x] = 1;
	flag_col[y] = 1;
        Stack_Push(&s, xy);
        
        while (s.size > 0)
        {
                xy = Stack_Top(&s);
                Stack_Pop(&s);
                i = xy/row_width;
                j = xy%row_width;
                if (flag_lattice[i][j] != 1)
                {
                        flag_lattice[i][j] = 1;         //mark the node popped
                        neighbours = get_neighbours(bond_lattice, xy, col_depth, row_width);
                        count++;
                        //north
                        if (neighbours.north > 0)              //if the site is seeded and not visited
                        {
                                i = neighbours.north/row_width;
                                j = neighbours.north%row_width;
                                Stack_Push(&s, neighbours.north);      //put the node in stack
                                flag_row[i] = 1;                        //record percolated level
                                flag_col[j] = 1;                        //record percolated level
                        }
                        //south
                        if (neighbours.south > 0)              //if the site is seeded and not visited
                        {
                                i = neighbours.south/row_width;
                                j = neighbours.south%row_width;
                                Stack_Push(&s, neighbours.south);
                                flag_row[i] = 1;
                                flag_col[j] = 1;
                        }
                        //west
                        if (neighbours.west > 0)               //if the site is seeded and not visited
                        {
                                i = neighbours.west/row_width;
                                j = neighbours.west%row_width;
                                Stack_Push(&s, neighbours.west);
                                flag_row[i] = 1;
                                flag_col[j] = 1;
                        }                        
			//east
                        if (neighbours.east > 0)               //if the site is seeded and not visited
                        {
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
        for (int i = 0; i < col_depth; i++)
        {
                if (flag_row[i] != 1)
		{
                        pdfs.row = 0;
			//break;
		}
        }
	free(flag_row);
        for (int j = 0; j < row_width; j++)
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



