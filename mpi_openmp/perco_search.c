#include "project2.h" 

void perco_search(int *cluster_size, int *prow, int *pcol, char sob)
{
	*prow = 1;	//default percolated
	*pcol = 1;
	*cluster_size = 0;
	int *flag_row = calloc(SITE_C-1, sizeof(int));
	int *flag_col = calloc((SITE_R-1), sizeof(int));
	if (sob == 's')
	{
		int *visited = calloc(SITE_R*SITE_C, sizeof(int));
		for (int i = 1; i < SITE_R; i++)
		{
			for (int j = 0; j < SITE_C; j++)
			{
				int ij = i*SITE_C+j;	//current node
				if (lattice[ij] > 0)
				{
					int current = ij;
					int above = current-SITE_C;
					if (lattice[above] > 0 && visited[above] == 0)
					{
						flag_col[i-1] = 1;
						int pos = above;
						while(pos >= (i-1)*SITE_C && lattice[pos] > 0)
						{
							visited[pos] = 1;
							pos--;
						}
						pos = above+1;
						while(pos < i*SITE_C && lattice[pos] > 0)
						{
							visited[pos] = 1;
							pos++;
						}

						struct Stack s;
						Stack_Init(&s);
						lattice[current] += lattice[above];
						//connected left nodes
						while(current >= i*SITE_C && lattice[current] > 0)
						{
							Stack_Push(&s, current);
							current--;
						}
						current = ij+1;	//node below's right
						//connected right nodes
						while(current < (i+1)*SITE_C && lattice[current] > 0)
						{
							Stack_Push(&s, current);
							current++;
						}
						while(s.size > 0)
						{
							int tmp = Stack_Top(&s);
							Stack_Pop(&s);
							lattice[tmp] = lattice[ij];
							//visited[tmp] = 1;
						}
						if (lattice[ij] > *cluster_size)
						{
							*cluster_size = lattice[ij];
							//printf("current size is %d\n", *cluster_size);
						}
					}//end if 2
				}//end if 1
				if (lattice[i+SITE_C*j] > 0 && lattice[i+SITE_C*j-1] > 0)
				{
					flag_row[i-1] = 1;
				}
/*		deals with v-shaped cluster
				else
				{
					int pos = ij-SITE_C;
					while(pos >= (i-1)*SITE_C && lattice[pos] > 0)
					{
						visited[pos] = 0;
						pos--;
					}
					pos = ij-SITE_C+1;
					while(pos < i*SITE_C && lattice[pos] > 0)
					{
						visited[pos] = 0;
						pos++;
					}
				}
*/

			}//end for 2
		}//end for 1
		for (int i = 0; i < SITE_R-1; i++)
		{
			if (flag_col[i] == 0)
				*pcol = 0;
			if (flag_row[i] == 0)
				*pcol = 0;
			
		}
	}
	else
	{

	}

}
