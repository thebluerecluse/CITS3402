/*  Zhiwei Huang    21450851        
    Ken Di Vincenzo 21946068
*/

#include "percolation.h"

struct Nbrs get_neighbours (int xy, int col_depth, int row_width)
{
        int x = 0;
        int y = 0;
        int xx = 0;
        int yy = 0;
        struct Nbrs cell;

        x = xy/row_width;
        y = xy%row_width;

        //north x-1, y remained
        if (x-1 < 0) {
                xx = col_depth-1;
        } else {
                xx = x-1;
        }

        cell.north = cell_transition(xx, y);
/*
        if (lattice[xx][y] != 0 && flag_lattice[xx][y] == 0) {
                cell.north = cell_transition(xx, y);
        } else {
                cell.north = -1;
        }
*/

        //south x+1, y remained
        if (x+1 >= col_depth) {
                xx = 0;
        } else {
                xx = x+1;
        }

        cell.south = cell_transition(xx, y);

        //west y-1, x remained
        if (y-1 < 0) {
                yy = row_width-1;
        } else {
                yy = y-1;
        }

        cell.west = cell_transition(x, yy);

        //east y+1, x remained
        if (y+1 >= row_width) {
                yy = 0;
        } else {
                yy = y+1;
        }

        cell.east = cell_transition(x, yy);

        return cell;
}

struct Perc_size DFS_site(int x, int y, int col_depth, int row_width)
{
        struct Nbrs neighbours;         //Nbrs structure store the neighbours of current node
        struct Stack s;                 //stack for DFS
        Stack_Init(&s);
        long long int xy;               //single value record the Nbrsition

	int *flag_row = calloc(col_depth , sizeof(int));
        int *flag_col = calloc(row_width , sizeof(int));
        
        int i = x;              //row coordinate of a site
        int j = y;              //column coordinate of a site
        int count = 0;          //count the cluster size
        struct Perc_size pdfs;  //be returned with percolated levels and size of cluster

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
                        neighbours = get_neighbours(xy, col_depth, row_width);
                        count++;

                        //north
                        if (site_lattice[neighbours.north/N][neighbours.north%N] == 1 && flag_lattice[neighbours.north/N][neighbours.north%N] == 0) {            //if the site is seeded and not visited
                        
                                i = neighbours.north/row_width;
                                j = neighbours.north%row_width;
                                Stack_Push(&s, neighbours.north);       //put the node in stack
                                flag_row[i] = 1;                        //record percolated level
                                flag_col[j] = 1;                        //record percolated level
                        }

                        //south
                        if (site_lattice[neighbours.south/N][neighbours.south%N] == 1 && flag_lattice[neighbours.south/N][neighbours.south%N] == 0) {             //if the site is seeded and not visited
                        
                                i = neighbours.south/row_width;
                                j = neighbours.south%row_width;
                                Stack_Push(&s, neighbours.south);
                                flag_row[i] = 1;
                                flag_col[j] = 1;
                        }

                        //west
                        if (site_lattice[neighbours.west/N][neighbours.west%N] == 1 && flag_lattice[neighbours.west/N][neighbours.west%N] == 0) {              //if the site is seeded and not visited
                        
                                i = neighbours.west/row_width;
                                j = neighbours.west%row_width;
                                Stack_Push(&s, neighbours.west);
                                flag_row[i] = 1;
                                flag_col[j] = 1;
                        }

			//east
                        if (site_lattice[neighbours.east/N][neighbours.east%N] == 1 && flag_lattice[neighbours.east/N][neighbours.east%N] == 0) {              //if the site is seeded and not visited
                        
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
        for (int i = 0 ; i < col_depth ; i++) {
                if (flag_row[i] != 1) {
                        pdfs.row = 0;
			//break;
		}
        }
        free(flag_row);
        
        for (int j = 0 ; j < row_width ; j++) {
                if (flag_col[j] != 1) {
                        pdfs.col = 0;
			//break;
		}
        }
        free(flag_col);
        
        pdfs.size = count;
        return pdfs;
}



