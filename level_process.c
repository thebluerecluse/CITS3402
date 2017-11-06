#include "project2.h"

int * level_process(int send_count, int *sub_lattice, char sob)
{
	if (sob == 's')
	{
		int num_row;
		if (send_count%SITE_C == 0)
			 num_row = send_count/SITE_C;

		omp_set_num_threads(NUM_THREADS);
		#pragma omp parallel
		#pragma omp for
		for (int i = 0; i < num_row; i++)
		{
			for (int j = 0; j < SITE_C; j++)
			{
				int orc = i*SITE_C+j;
				int *visited = calloc(send_count, sizeof(int));
				if (sub_lattice[orc] == 1 && visited[orc] == 0)
				{
					int count = 0;
					struct Stack s;
					Stack_Init(&s);
					int rc = orc;

					while(rc >= i*SITE_C && sub_lattice[rc] == 1 && visited[rc] == 0)
					{
						Stack_Push(&s, rc);
						count++;
						visited[rc] = 1;	//mark this site
						rc--;	//neighbours on the left
					}
					rc = orc+1;	//set to origin's right
					while(rc < (i+1)*SITE_C && sub_lattice[rc] == 1 && visited[rc] == 0)
					{
						Stack_Push(&s, rc);
						count++;
						visited[rc] = 1;	//mark this site
						rc++;	//neighbours on the right
					}
					while(s.size > 0)
					{
						int topped = Stack_Top(&s);
						Stack_Pop(&s);
						sub_lattice[topped] = count;
					}
				}
				
			}
		}
	}
	else if (sob == 'b')
	{
		
	}
	else
	{
		printf("Invalid type of percolation\n");
		exit(1);
	}
	return sub_lattice;
}
