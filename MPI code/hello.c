#include <mpi.h>  //ignore warning on this line
#include <stdio.h> 

   int main(int argc, char **argv){
		int id, procs, err; // variables available to all processors

		// initialize MPI_Init
		err = MPI_Init(&argc, &argv);
		if (err != MPI_SUCCESS){
		  printf("\nError initializing MPI.\n");
		  MPI_Abort(MPI_COMM_WORLD, err);
		}

		// returns no of processors, stores in procs
		MPI_Comm_size(MPI_COMM_WORLD,&procs);
		
		// returns processor id, stores in id
		MPI_Comm_rank(MPI_COMM_WORLD,&id);
		
		printf("\tI am processor %d: Total No. of processors =  %d.\n", id, procs);
		printf("\tHello from processor %d.\n", id);
		//all the above print instructions will be executed by all the processors
		MPI_Finalize();
		return 0;  

   }

// to run use following instructions
// mpicc hello.c
// mpiexec -np 3 ./a.out