#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <mpi.h>
#define mpc MPI_COMM_WORLD

//Given the condition that n is divisible by p
//mpirun -n p ./a.out n filename

int findmax(int* data,int arrsize){
    int max=data[0];
    for(int i=0;i<arrsize;i++){
        if(data[i]>=max){
            max=data[i];
        }
    }
    return max;
}

int main(int argc, char** argv){

    int p,id,err;
    int* arr,n;
    int* temparr,localmax;
    int* maxarr;
    
    MPI_Status status;
    err = MPI_Init(&argc,&argv);
    if (err != MPI_SUCCESS){
        printf("MPI Initialisation Error \n");
        MPI_Abort(mpc,err);
    }

    MPI_Comm_size(mpc,&p);
    MPI_Comm_rank(mpc,&id);
    
    n=atoi(argv[1]); 
    arr =(int*)malloc(n*sizeof(int)); // complete array only at master,because file read only at master
    temparr=(int*)malloc((n/p)*sizeof(int));// each processor will have copy with their own n/p size data
    maxarr=(int*)malloc(p*sizeof(int)); //to store local maxima from all processors' data

    if (id==0){
        // Import data from file
        FILE* fptr;
        char* fname;
        fname =argv[2];
        fptr=fopen(fname,"r");
        //store all data in array
        for(int i=0;i<n;i++){
            fscanf(fptr,"%d",&arr[i]);
            //print all data in user friendly way
            printf("%6d",arr[i]);
            if ((i+1) % 10 == 0) printf("\n");
        }
        printf("\n");
        fclose(fptr);
        //now send n/p data to all slaves
        for(int i=1;i<p;i++){
            MPI_Send(arr + (i*(n/p)), n/p, MPI_INT, i, 0, mpc);    
        }
        //assign first n/p data elements to master's temparr
        for(int i=0;i<n/p;i++){
            temparr[i]=arr[i];
        }     
    }
    else{
        //receive at all slave processors their own n/p  size data
        MPI_Recv(temparr, n/p, MPI_INT, 0, 0,  mpc, &status);     
    }
    // now find local max at each processor, and send back to master

    if(id!=0){
        localmax=findmax(temparr,n/p);
        MPI_Send(&localmax,1,MPI_INT,0,1,mpc);
    }
    if(id==0){
        maxarr[0]=findmax(temparr,n/p);
        for(int i=1;i<p;i++){
            MPI_Recv(&maxarr[i], 1, MPI_INT, i, 1, mpc,&status);    
        }
        printf("%d \n",findmax(maxarr,p));
    }
    MPI_Finalize();
    return 0;
}