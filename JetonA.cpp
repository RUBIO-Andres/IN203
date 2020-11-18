# include <iostream>
# include <cstdlib>
#include <stdlib.h>
# include <mpi.h>
# include <sstream>
# include <fstream>

using namespace std;

int main(int nargs, char *argv[])
{
    int rank, nbp, val, tag =1;
    int send = 6;
    MPI_Init(&nargs, &argv);
    MPI_Comm comm;
    MPI_Comm_dup(MPI_COMM_WORLD, &comm);
    MPI_Comm_size(comm, &nbp);
    MPI_Comm_rank(comm, &rank);
    MPI_Status Stat; 

    if(rank == 0)
    {
        MPI_Send(&send , 1, MPI_INT , rank +1, tag, MPI_COMM_WORLD);
        MPI_Recv(&val , 1, MPI_INT ,  nbp-1, tag, MPI_COMM_WORLD , &Stat);
        cout << "Process " << rank << " received " << val << " from process "<< nbp-1<<"and send"<<send << " to the process "<< 1 <<".\n";
    }
    else if(rank == nbp-1)
    {
        MPI_Recv(&val , 1, MPI_INT , rank-1 , tag, MPI_COMM_WORLD , &Stat);
        val+=1;
        MPI_Send(&val , 1, MPI_INT , 0 , tag, MPI_COMM_WORLD);
        cout << "Process " << rank << " received " << val-1 << " from process "<< rank-1<< " and send " << val << " to the process "<< 0 <<".\n";
    }
    else
    {
        MPI_Recv(&val , 1, MPI_INT , rank-1 , tag, MPI_COMM_WORLD , &Stat);
        val+=1;
        MPI_Send(&val , 1, MPI_INT , rank+1 , tag, MPI_COMM_WORLD);
        cout << "Process " << rank << " received " << val-1 << " from process "<< rank-1<< " and send " << val << " to the process "<< rank +1 <<".\n";
    }
    MPI_Finalize();
    return EXIT_SUCCESS;
}