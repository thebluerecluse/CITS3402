/*  Zhiwei Huang    21450851        
    Ken Di Vincenzo 21946068
*/

#include "percolation.h"

struct Pos get_neighbours (int xy, int col_depth, int row_width)
{
        int x = 0;
        int y = 0;
        int xx = 0;
        int yy = 0;
        struct Pos cell;

        x = xy/row_width;
        y = xy%row_width;

        //north x-1, y remained
        if (x-1 < 0)
                xx = col_depth-1;
        else
                xx = x-1;
        if (site_lattice[xx][y] == 1 && flag_lattice[xx][y] == 0)
                cell.north = cell_transition(xx, y, row_width);
        else
                cell.north = -1;
        //south x+1, y remained
        if (x+1 >= col_depth)
                xx = 0;
        else
                xx = x+1;
        if (site_lattice[xx][y] == 1 && flag_lattice[xx][y] == 0)
                cell.south = cell_transition(xx, y, row_width);
        else
                cell.south = -1;
        //west y-1, x remained
        if (y-1 < 0)
                yy = row_width-1;
        else
                yy = y-1;
        if (site_lattice[x][yy] == 1 && flag_lattice[x][yy] == 0)
                cell.west = cell_transition(x, yy, row_width);
        else
                cell.west = -1;
        //east y+1, x remained
        if (y+1 >= row_width)
                yy = 0;
        else
                yy = y+1;
        if (site_lattice[x][yy] == 1 && flag_lattice[x][yy] == 0)
                cell.east = cell_transition(x, yy, row_width);
        else
                cell.east = -1;

        return cell;
}
struct perco_size DFS_site(int x, int y, int col_depth, int row_width)
{
        struct Pos pos; //pos structure store the neighbours of current node
        struct Stack s;//stack for DFS
        Stack_Init(&s);
        long long int xy;         //single value record the position
        //int flag_row[col_depth];        //mark percolated level in row direction
        //memset(flag_row, 0, col_depth * sizeof(flag_row));
	int *flag_row = calloc(col_depth , sizeof(int));
	//fprintf(stderr,"seg fault after flag_row");

        //int flag_col[row_width];        //mark percolated level in column direction
        //memset(flag_col, 0, row_width * (sizeof flag_col));
	int *flag_col = calloc(row_width , sizeof(int));
	//fprintf(stderr,"seg fault after flag_col");
        int i = x;      //row coordinate of a site
        int j = y;      //column coordinate of a site
        int count = 0;  //count the cluster size
        struct perco_size pdfs; //be returned with percolated levels and size of cluster

        //perform dfs
        xy = cell_transition(x,y,col_depth);
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
                        pos = get_neighbours(xy, col_depth, row_width);
                        count++;
                        //north
                        if (pos.north > 0)              //if the site is seeded and not visited
                        {
                                i = pos.north/row_width;
                                j = pos.north%row_width;
                                Stack_Push(&s, pos.north);      //put the node in stack
                                flag_row[i] = 1;                        //record percolated level
                                flag_col[j] = 1;                        //record percolated level
                        }
                        //south
                        if (pos.south > 0)              //if the site is seeded and not visited
                        {
                                i = pos.south/row_width;
                                j = pos.south%row_width;
                                Stack_Push(&s, pos.south);
                                flag_row[i] = 1;
                                flag_col[j] = 1;
                        }
                        //west
                        if (pos.west > 0)               //if the site is seeded and not visited
                        {
                                i = pos.west/row_width;
                                j = pos.west%row_width;
                                Stack_Push(&s, pos.west);
                                flag_row[i] = 1;
                                flag_col[j] = 1;
                        }                        
			//east
                        if (pos.east > 0)               //if the site is seeded and not visited
                        {
                                i = pos.east/row_width;
                                j = pos.east%row_width;
                                Stack_Push(&s, pos.east);
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



