# CITS3402

Zhiwei Huang    21450851        
Ken Di Vincenzo 21946068

A C program for simulating 2D lattice percolation in a finite sized lattice with wrap-around. 

With a C compiler installed, each program can be compiled with the supplied Makefile with the terminal command ‘make’. The sequential and parallelized have their own folders.
The lattice size and number of parallel threads invoked can be changed by modifying the pre-processor values N and NUM_THREADS in the percolation.h header file. 

The program can then be run by calling the executable and supplying three command line arguments. The usage is as follows:

./percolation  [ ‘s’ | ‘b’ ]  [ 0 < p < 1 ]  [ 0 | 1 | 2 ]

The first command line argument, either ‘s’ or ‘b’, refers to the type of lattice percolation - site or bond. The second argument, p, is the seed probability. The third argument refers to the direction of percolation ie column, row, or both.
