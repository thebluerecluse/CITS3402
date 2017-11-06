#include "project2.h"

void generate_lattice(char sob)
{
	if (sob == 's')
	{
		lattice = calloc(SITE_R*SITE_C, sizeof(int));
	}
	else if (sob == 'b')
	{
		lattice = calloc(BOND_R*BOND_C, sizeof(int));
	}
	else
	{
		printf("invalid lattice type\n");
		exit(1);
	}
}

void fill_lattice(double p, char sob)
{
	//srand(time(NULL));
	double r = 0.0;
	if (sob == 's')
	{
		for (int i = 0; i < SITE_R*SITE_C; i++)
		{
			r = (double)rand()/(double)RAND_MAX;
			if (r < p)
			{
				lattice[i] = 1;
			}
		}
	}
	else
	{
		for (int i = 0; i < SITE_R*BOND_C; i++)
		{
			r = (double)rand()/(double)RAND_MAX;
			if (r < p)
			{
				lattice[i] = 1;
			}
		}
		
	}

}

void transpose_lattice(char sob)
{
	if (sob == 's')
	{
		int **tmp = malloc(SITE_R*SITE_C * sizeof(int *));
		int **tmp2 = malloc(SITE_R*SITE_C * sizeof(int *));
		for (int i = 0; i < SITE_R; i++)
		{
			*tmp = malloc(SITE_C * sizeof(int));
			*tmp2 = malloc(SITE_C * sizeof(int));
		}
		for (int i = 0; i < SITE_R; i++)
		{
			for (int j = 0; j < SITE_C; j++)
			{
				tmp[i][j] = lattice[i*SITE_R+j];
			}
		}
		for (int i = 0; i < SITE_R; i++)
		{
			for (int j = 0; j < SITE_C; j++)
			{
				tmp2[i][j] = tmp[j][i];
			}
		}
		for (int i = 0; i < SITE_R; i++)
		{
			for (int j = 0; j < SITE_C; j++)
			{
				lattice_for_row[i*SITE_R+j] = tmp[i][j];
			}
		}

		for (int i = 0; i < SITE_R*SITE_C; i++)
		{
			lattice_for_row[i] = lattice[SITE_R*i - ((i/SITE_R) * (SITE_R*SITE_C - 1))];
		}
	}
	else
	{
	
	}
}

void print_lattice(char sob)
{
	if (sob == 's')
	{
		for (int i = 0; i < SITE_R; i++)
		{
			for (int j = 0; j < SITE_C; j++)
			{
				printf("%d\t", lattice[i*SITE_R+j]);
			}
			printf("\n");
		}
	}
	else
	{
		for (int i = 0; i < BOND_R; i++)
		{
			for (int j = 0; j < BOND_C; j++)
			{
				printf("%d\t", lattice[i*j]);
			}
			printf("\n");
		}
	}
}

void print_row_lattice(char sob)
{
	if (sob == 's')
	{
		for (int i = 0; i < SITE_R; i++)
		{
			for (int j = 0; j < SITE_C; j++)
			{
				printf("%d", lattice_for_row[i*SITE_R+j]);
			}
			printf("\n");
		}
	}
	else
	{
		for (int i = 0; i < BOND_R; i++)
		{
			for (int j = 0; j < BOND_C; j++)
			{
				printf("%d", lattice_for_row[i*j]);
			}
			printf("\n");
		}
	}
}
