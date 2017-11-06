/*  Zhiwei Huang    21450851        
    Ken Di Vincenzo 21946068
*/

#include "percolation.h"

// using braces around initializer/matrix of site or bond generation
int **vbond_lattice;
int **hbond_lattice;

// change the position into a single value
int cell_transition (int x, int y, int col_depth)
{
	return (x)*N+y;
}

struct perco_size start_point (int col_depth, int row_width, int **lattice, char s_or_b)
{
	struct perco_size ps;
	struct perco_size result;
	int row = 0;
	int col = 0;
	int max = 0;

	//start dfs
	for (int i = 0; i < col_depth; i++)
	{
		for (int j = 0; j < row_width; j++)
		{
			if (flag_lattice[i][j] != 1 && lattice[i][j] == 1 && s_or_b == 's')
			{
				ps = DFS_site(i, j, col_depth, row_width); 
				if (ps.size > max)		//record maximum size so far
				{
					max = ps.size;
				}
				if (ps.row == 1)	//if ps.row is 1, column percolates
					col = 1;	
				if (ps.col == 1)	//if ps.col is 1, row percolates
					row = 1;	
			}
			if (flag_lattice[i][j] != 1 && lattice[i][j] == 1 && s_or_b == 'b')
			{
				ps = DFS_bond(i, j, col_depth, row_width); 
				if (ps.size > max)		//record maximum size so far
				{
					max = ps.size;
				}
				if (ps.row == 1)	//means col percolates
					col = 1;	//so result.col records the column percolation
				if (ps.col == 1)	//means row percolates
					row = 1;	//so result.row records the row percolation
			}
		}
	}
	result.row = col;	//
	result.col = row;
	result.size = max;
	return result;
}

//percolation starts form the initial row or column
void percolate (int choice, char s_or_b, int *percoTF, int *size, double p)
{
	struct perco_size result;	//for row direction left to right
	
	if (s_or_b == 's')		//site percolation
	{
		site_lattice = generate_lattice(N, N);		//create empty site lattice
		flag_lattice = generate_lattice(N, N);		//initialise flag lattice
		fill_lattice(site_lattice, N, N, p);		//fill in site lattice with threshold
		result = start_point(N, N, site_lattice, s_or_b);			//iterate each point in lattice for dfs
		*size = result.size;
		//check given result
		switch (choice)
		{
			case 0:		//row percolate, col index marked
				*percoTF = result.col;
				break;
			case 1:		//col percolate, row index marked
				*percoTF = result.row;
				break;
			case 2:		//both percolate, row and col both marked
				if (result.row == 1 && result.col == 1)
					*percoTF = 1;
				break;
			default:
				printf("invalid percolation direction site percolation\n");
				exit(-1);
		}
	}
	else if (s_or_b == 'b')		//bond percolation
	{
		hbond_lattice = generate_lattice(N, N);		//horizontal bonds
		fill_lattice(hbond_lattice, N, N, p);
		vbond_lattice = generate_lattice(N, N);		//vertical bonds
		fill_lattice(vbond_lattice, N, N, p);

		bond_lattice = generate_lattice(2*N, N);
		flag_lattice = generate_lattice(2*N, N);
		//merge horizontal and vertical bonds to become one matrix
		for (int i = 0; i < 2*N; i++)
		{
			for (int j = 0; j < N; j++)
			{	//fill the odd number row
				bond_lattice[i][j] = hbond_lattice[i/2][j];
			}
			i++;
			//for (int k = N-1; k > 0; k--)
			for (int k = 0; k < N; k++)
			{	//fill the even number row
				bond_lattice[i][k] = vbond_lattice[i/2][k];
			}
		}

		result = start_point(2*N, N, bond_lattice, s_or_b);
		*size = result.size;
		switch (choice)		//percolation directions
		{
			case 0:		//rows
				*percoTF = result.col;
				break;
			case 1:		//columns
				*percoTF = result.row;
				break;
			case 2:		//rows and columns
				if (result.row == 1 && result.col == 1)
					*percoTF = 1;
				break;
			default:
				printf("invalid percolation direction of bond percolation\n");
				exit(-1);
		}
	}
	else
	{
		printf("invalid percolation type\n");
		exit(-1);
	}
}

void print_lattice (char s_or_b, int m, int n)
{
	if (s_or_b == 's')
	{
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				printf("%d", site_lattice[i][j]);
			}
			printf("\n");
		}
	}
	if (s_or_b == 'b')
	{
		for (int i = 0; i < 2*m; i++) {
			for (int j = 0; j < n; j++) {
				printf("%d", bond_lattice[i][j]);
			}
			printf("\n");
		}
		
	}
}

int main (int argc, char *argv[])
{
    char s_or_b = '\0';          //site or bond percolation
    double p = 0.0;                //probability to generate lattice
	int choice = 0;             //percolate 0-horizontal, 1-vertical, 2-both
	int	percoTF = 0;		//wheterh percolate or not
	int	size = 0;		//size of the cluster
    struct  timeval start, end;

    if (argc != 4)
    {
        printf("arguments <executable> <'s' or 'b'> <probability> <0, horizontal, 1, vertical, 2, both>\n");
        exit(-1);
    } else {
	 	s_or_b = *argv[1];
		p = atof(argv[2]);
		choice = atoi(argv[3]);
	}

	//time consumed  
	gettimeofday(&start, NULL);

	percolate(choice, s_or_b, &percoTF, &size, p);
	if (percoTF == 1)
		printf("your choice percolates and the maximum size of cluster is %d\n", size);
	else
		printf("your choice does not percolate in the direction expected(row, col, or both) and the maximum size of cluster is %d\n", size);

	print_lattice(s_or_b, N, N);

	if (s_or_b == 's')
	{
		free_lattice(site_lattice, N);
	}
	if (s_or_b == 'b')
	{
		free_lattice(hbond_lattice, N);
		free_lattice(vbond_lattice, N);
		free_lattice(bond_lattice, 2*N);
	}
	free_lattice(flag_lattice, N);
	
	gettimeofday(&end, NULL);
	double delta = ((end.tv_sec - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;

    printf("time consumed = %12.10f\n", delta);
}
