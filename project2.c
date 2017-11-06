#include "project2.h" 

int main (int argc, char *argv[])
{
        char    sob = '\0';          //site or bond percolation
        double  p = 0.0;                //probability to generate lattice
        int     choice = 0;             //percolate 0-horizontal, 1-vertical, 2-both
        struct  timeval start, end;

        if (argc != 4)
        {
                printf("arguments <executable> \
		<'s' or 'b'> <probability> <0, horizontal, 1, vertical, 2, both>\n");
                exit(-1);
        } else
        {
                sob = *argv[1];
                p = atof(argv[2]);
                choice = atoi(argv[3]);
        }
        //time consumed  
        gettimeofday(&start, NULL);

	int size, rank, send_count, rc = 0;
	MPI_Init(&argc, &argv);
//	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if (size % 2 != 0)
	{
		printf("Quitting. Number of MPI tasks must be divisible by 2.\n");
		MPI_Abort(MPI_COMM_WORLD, rc);
		exit(0);
	}
	send_count = send_length(size, sob);

	if (rank == MASTER)
	{
		generate_lattice(sob);
		fill_lattice(p, sob);
		//transpose_lattice(sob);
	}
	int *sub_lattice = malloc(send_count * sizeof(int));
	int recv_count = send_count;
	//scatter the lattice to all processes
	MPI_Scatter(lattice, send_count, MPI_INT, sub_lattice, recv_count, MPI_INT, MASTER, MPI_COMM_WORLD);

	/* operations of all processes START*/
	sub_lattice = level_process(send_count, sub_lattice, sob);
	/* operations on sub lattices END*/

	MPI_Gather(sub_lattice, recv_count, MPI_INT, lattice, send_count, MPI_INT, MASTER, MPI_COMM_WORLD);
	free(sub_lattice);
	
	if(rank == MASTER)
	{
		int cluster_size, rowp, colp;
		perco_search(&cluster_size, &rowp, &colp, sob);

		if (colp == 1 && choice == 1)
			printf("lattice percolates vertically\n");
		else if (choice == 1)
			printf("lattice dose not percolate vertically\n");
		if (rowp == 1 && choice == 0)
			printf("lattice percolates horizontally\n");
		else if (choice == 0)
			printf("lattice dose not percolate horizontally\n");
		free(lattice);
		if (colp == 1 && rowp == 1 && choice == 2)
			printf("lattice percolates in both directions\n");
		else if (choice == 2)
			printf("lattice does not percolate in both directions\n");

	}
	MPI_Finalize();

        gettimeofday(&end, NULL);
        double delta = ((end.tv_sec - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
	
	if (rank == MASTER)
	{
        	printf("time consumed = %12.10f\n", delta);
	}
}

