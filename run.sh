#PBS -l nodes=4:ppn=1
source /etc/bash.bashrc
mpirun project2 s 0.5 1
