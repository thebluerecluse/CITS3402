/*  Zhiwei Huang    21450851        
    Ken Di Vincenzo 21946068
*/

// Depth-first search functions for bond lattice

#include "percolation.h"

struct Bond_cell get_bond_neighbours (int xy, int col_depth, int row_width)
{
        int x = 0;
        int y = 0;
        int left_up = 0;	//horizontal left or vertical up bond
	int left1 = 0;		//horizontal up-left or vertical right-up
	int left2 = 0;		//horizontal up-right or vertical right-down
	//col index
        int right_down = 0;	//horizontal right or vertical down
	int right1 = 0;		//horizontal down-right or vertical left-down
	int right2 = 0;		//horizontal down-left or vertical left-up
        struct Bond_cell cell;

        x = xy/row_width;	//row index
        y = xy%row_width;	//col index

	if (x % 2 == 0)		//it is a horizontal bond********************
	{
		//west side, clock1
		if (y-1 < 0)
			left_up = row_width-1;
		else
			left_up = y-1;
		if (bond_lattice[x][left_up] == 1 && flag_lattice[x][left_up] == 0)
			cell.clock1 = cell_transition(x, left_up, row_width);
		else
			cell.clock1 = -1;
		//east side, clock4
		if(y+1 >= row_width)
			right_down = 0;
		else
			right_down = y+1;
		if (bond_lattice[x][right_down] == 1 && flag_lattice[x][right_down] == 0)
			cell.clock4 = cell_transition(x, right_down, row_width);
		else
			cell.clock4 = -1;
		//north side, two bonds
		//north left, clock2
		if (x-1 < 0)
			left1 = col_depth-1;
		else
			left1 = x-1;
		if (bond_lattice[left1][y] == 1 && flag_lattice[left1][y] == 0)
			cell.clock2 = cell_transition(left1, y, row_width);
		else
			cell.clock2 = -1;
		//north right, clock3
		if (y+1 >= row_width)
			left2 = row_width-1;
		else
			left2 = y+1;
		if (bond_lattice[left1][left2] == 1 && flag_lattice[left1][left2] == 0)
			cell.clock3 = cell_transition(left1, left2, row_width);
		else
			cell.clock3 = -1;
		//south sied, two bonds
		//south right, clock5
		right1 = x+1;		//should never be greater than col_depth
		if (y+1 >= row_width)
			right2 = 0;
		else
			right2 = y+1;
		if (bond_lattice[right1][right2] == 1 && flag_lattice[right1][right2] == 0)
			cell.clock5 = cell_transition(right1, right2, row_width);
		else
			cell.clock5 = -1;
		//south left
		if (bond_lattice[right1][y] == 1 && flag_lattice[right1][y] == 0)
			cell.clock6 = cell_transition(right1, y, row_width);
		else
			cell.clock6 = -1;
	}
	else			//it is a vertical bond***********************
	{
		//north side, clock1
		if (x-2 < 0)
			left_up = col_depth-1;
		else
			left_up = x-2;
		if (bond_lattice[left_up][y] == 1 && flag_lattice[left_up][y] == 0)
			cell.clock1 = cell_transition(left_up, y, row_width);
		else
			cell.clock1 = -1;
		//south side, clock4 
		if (x+2 >= col_depth)
			right_down = 0;
		else
			right_down = x+2;
		if (bond_lattice[right_down][y] == 1 && flag_lattice[right_down][y] == 0)
			cell.clock4 = cell_transition(right_down, y, row_width);
		else
			cell.clock4 = -1;
		//east side, two bonds
		//east up, clock2
		left1 = x-1;			//should never be less than 0
		if (bond_lattice[left1][y] == 1 && flag_lattice[left1][y] == 0)
			cell.clock2 = cell_transition(left1, y, row_width);
		else
			cell.clock2 = -1;
		//east down, clock3
		if (x+1 >= col_depth)
			left2 = 0;
		else
			left2 = x+1;
		if (bond_lattice[left2][y] == 1 && flag_lattice[left2][y] == 0)
			cell.clock3 = cell_transition(left2, y, row_width);
		else
			cell.clock3 = -1;
		//west side, two bonds
		//west down, clock5
		if (x+1 >= col_depth)
			right1 = 0;
		else
			right1 = x+1;
		if (y-1 < 0)
			right2 = row_width-1;
		else
			right2 = y-1;
		if (bond_lattice[right1][right2] == 1 && flag_lattice[right1][right2] == 0)
			cell.clock5 = cell_transition(right1, right2, row_width);
		else
			cell.clock5 = -1;
		//west up, clock6
		right1 = x-1;
		if (y-1 < 0)
			right2 = row_width-1;
		if (bond_lattice[right1][right2] == 1 && flag_lattice[right1][right2] == 0)
			cell.clock6 = cell_transition(right1, right2, row_width);
		else
			cell.clock6 = -1;
	}

        return cell;
}
struct perco_size DFS_bond(int x, int y, int col_depth, int row_width)
{
        struct Bond_cell bond; //bond structure store the neighbours of current node
        struct Stack s;//stack for DFS
        Stack_Init(&s);
        int xy;         //single value record the bondition
        //int flag_row[col_depth];        //mark percolated level in row direction
        //memset(flag_row, 0, sizeof flag_row);
	int *flag_row = calloc(col_depth , sizeof(int));
	fprintf(stderr, "seg fault after flag_row\n");
	int *flag_col = calloc(row_width , sizeof(int));
        //int flag_col[row_width];        //mark percolated level in column direction
        //memset(flag_col, 0, sizeof flag_col);
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
                        bond = get_bond_neighbours(xy, col_depth, row_width);
			count++;
                        //north
                        if (bond.clock1 > 0)              //if the site is seeded and not visited
                        {
                                i = bond.clock1/row_width;
                                j = bond.clock1%row_width;
                                Stack_Push(&s, bond.clock1);      //put the node in stack
                                flag_row[i] = 1;                        //record percolated level
                                flag_col[j] = 1;                        //record percolated level
                        }
                        //south
                        if (bond.clock2 > 0)              //if the site is seeded and not visited
                        {
                                i = bond.clock2/row_width;
                                j = bond.clock2%row_width;
                                Stack_Push(&s, bond.clock2);
                                flag_row[i] = 1;
                                flag_col[j] = 1;
                        }
                        //west
                        if (bond.clock3 > 0)               //if the site is seeded and not visited
                        {
				i = bond.clock3/row_width;
				j = bond.clock3%row_width;
                                Stack_Push(&s, bond.clock3);
                                flag_row[i] = 1;
                                flag_col[j] = 1;
                        }                        
			//east
                        if (bond.clock4 > 0)               //if the site is seeded and not visited
                        {
                                i = bond.clock4/row_width;
                                j = bond.clock4%row_width;
                                Stack_Push(&s, bond.clock4);
                                flag_row[i] = 1;
                                flag_col[j] = 1;
                        }
                        if (bond.clock5 > 0)               //if the site is seeded and not visited
                        {
                                i = bond.clock5/row_width;
                                j = bond.clock5%row_width;
                                Stack_Push(&s, bond.clock5);
                                flag_row[i] = 1;
                                flag_col[j] = 1;
                        }
                        if (bond.clock6 > 0)               //if the site is seeded and not visited
                        {
                                i = bond.clock6/row_width;
                                j = bond.clock6%row_width;
                                Stack_Push(&s, bond.clock6);
                                flag_row[i] = 1;
                                flag_col[j] = 1;
                        }
		
                }
        }
        
        pdfs.row = 1;
        pdfs.col = 1;
        for (int i = 1; i < col_depth; i+=2)
        {
                if (flag_row[i] != 1)
		{
                        pdfs.row = 0;
			//break;
		}
        }
        for (int j = 0; j < row_width; j++)
        {
                if (flag_col[j] != 1)
		{
                        pdfs.col = 0;
			//break;
		}
        }
        pdfs.size = count;
        return pdfs;
}



