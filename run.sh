#PBS -l nodes=8:ppn=4
source /etc/bash.bashrc
mpirun ./project2 s 0.5 2
