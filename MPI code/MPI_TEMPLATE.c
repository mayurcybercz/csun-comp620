#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <mpi.h>

#define mpc MPI_COMM_WORLD


int main(int argc, char** argv){

    int p,id; 
    int *arr,n; //declare all variables here to be accesible to all processors

    err = MPI_Init(&argc,&argv);
    if (err != MPI_Success){
        printf("MPI Initialisation Error \n");
        MPI_Abort(mpc,err);
    }

    MPI_Comm_size(mpc,&p);
    MPI_Comm_rank(mpc,&id);

    //assign values to variables here from arguments)
    n=atoi(argv[1]);
    arr=(int*)malloc(n*sizeof(int));

    if (id==0){
        //Master does this
    }
    else{
        //all (p-1) slaves does this
    }

    MPI_Finalize();
    return 0;
}