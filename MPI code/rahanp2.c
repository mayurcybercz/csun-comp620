#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <mpi.h>

#define mpc MPI_COMM_WORLD
#define BUFSIZE 

//Submission of Parallel Homework 2 by Mayur Rahangdale

// Note: 1) Have used 'int' and 'MPI_INT' in all the implementation , the program will work for all integer values of 4 byte size (-2,147,483,648 to 2,147,483,647)
// 2) This program will also run if n is not divisible by p (added zeroes to balance the data between processors)
// 3) Using MPI_Scatter and MPI_Gather for all the parallel implementation
// 4) Tested the code for 1000 input size and works fine

void printarr(int a[], int n, char *msg){
    int i;
	printf("\n%s\n", msg); 
    for(i = 0; i < n; i++){
	  printf("%3d ", a[i]); 
	  if ((i+1) % 10 == 0) printf("\n\t");
	}
    printf("\n");
 } 

int collapse_int(int num){
    int collapsed=0;
    char chararr[BUFSIZE];
    snprintf(chararr, sizeof(chararr), "%d", num);
    for(int i=0;i<(strlen(chararr));i++){
        int temp=chararr[i] - '0';
        collapsed=collapsed+temp;
    }
    if(collapsed>9){
        return collapse_int(collapsed);
    }
    else{
        return collapsed;
    }
}


int main(int argc, char** argv){

    int p,n,id,err; 
    int *arr,*tmp_arr,*local_collapse_store,*global_collapse_store,*temp_store; 

    err = MPI_Init(&argc, &argv);
    if (err != MPI_SUCCESS){
	printf("\nError initializing MPI.\n");
	MPI_Abort(mpc, err);
  } 

    MPI_Comm_size(mpc,&p);
    MPI_Comm_rank(mpc,&id);

    if (id == 0) {
	   if (argc < 3) {
		printf("\n\tOOOPS...., INVALID No of Arguements,\n"
		"\tTO RUN	mpiexec -n p a.out n anyinputfile solutionno\n"
		"\t\tp (integer) No.of Processors...\n"
		"\t\tn (integer) No. of inputs (size of array)...\n"
        "\t\tanyinputfile (string) Filepath...\n"
        "\t\tsoultionno (integer) Solutionno value 1/2/3/4...\n"    
		"\t\tThis code works even for n not divisble by p\n\n");
	   } 
      } 

      if (argc < 3) {
		  MPI_Finalize(); return 0;
	  }

    n=atoi(argv[1]);
    int new_n;
    // check if n divisible by p
    if((n%p)==0 ){
        new_n=n;
    }
    else{
    //convert n into a form so that it is divisible by p
    int zeroes_count= p-(n%p); // number of zeroes to add in n so that it becomes divisible by p
    new_n = n + zeroes_count;
    }

    //now the array of size new_n can be divided into p processors
    arr=(int*)malloc(new_n*sizeof(int));
    int solno = atoi(argv[3]);
    char exp=solno +'0';

    int k=new_n/p;
    tmp_arr=(int*)malloc(k*sizeof(int));
    local_collapse_store=(int*)malloc(k*sizeof(int));
    global_collapse_store=(int*)malloc(new_n*sizeof(int));
    temp_store=(int*)malloc(p*sizeof(int));


    if (id==0){
        //Master reads input
		FILE *inf;
		char *fname;
        fname = argv[2];  // get n
		inf = fopen(fname,"r");	// open finput file	
		for(int i = 0; i < n; i++)// read n numbers 
			fscanf(inf, "%d", &arr[i]);
		// end for
        //fill the remaining space of arr by zeroes
        for(int i =n;i<new_n;i++){
            arr[i]=0;
        }
		fclose(inf); 
    }
      
    //switch-case is used for switching into solution choice 
    switch (exp){
    case '1':
        MPI_Scatter(arr,k, MPI_INT,tmp_arr,k, MPI_INT, 0, mpc);
        int local_addition=0;
        for(int i=0;i<k;i++){
            local_addition=local_addition + tmp_arr[i];
        }
        MPI_Gather(&local_addition,1,MPI_INT,temp_store,1,MPI_INT,0,mpc);
        if(id==0){
            int global_addition=0;
            for(int i=0;i<p;i++){
                global_addition=global_addition + temp_store[i];
            }
            int global_collapse=collapse_int(global_addition);
            printf("%d\n",global_collapse);
        }
      
      break;

    case '2':
        MPI_Scatter(arr,k, MPI_INT,tmp_arr,k, MPI_INT, 0, mpc);
        for(int i=0;i<k;i++){
            local_collapse_store[i]=collapse_int(tmp_arr[i]);
           
        }
        MPI_Gather(local_collapse_store,k,MPI_INT,global_collapse_store,k,MPI_INT,0,mpc);
        if(id==0){
            int global_collapse_addition=0;
            for(int i=0;i<new_n;i++){
                global_collapse_addition=global_collapse_addition + global_collapse_store[i];
            }
            int global_collapse=collapse_int(global_collapse_addition);
            printf("%d\n",global_collapse);
        }
      break;

    case '3':
        MPI_Scatter(arr,k, MPI_INT,tmp_arr,k, MPI_INT, 0, mpc);
        for(int i=0;i<k;i++){
            local_collapse_store[i]=collapse_int(tmp_arr[i]);
        }
        int local_collapse_addition=0;
        for(int i=0;i<k;i++){
                local_collapse_addition=local_collapse_addition + local_collapse_store[i];
            }
        int local_collapse=collapse_int(local_collapse_addition);

        MPI_Gather(&local_collapse,1,MPI_INT,temp_store,1,MPI_INT,0,mpc);
        if(id==0){
            int temp_collapse_addition =0;
            for(int i=0;i<p;i++){
                temp_collapse_addition=temp_collapse_addition + temp_store[i];
            }
            int global_collapse=collapse_int(temp_collapse_addition);
            printf("%d\n",global_collapse);
        }

        break;
    
    case '4':
        //only master performs all the computations
        if(id==0){
            for(int i=0;i<new_n;i++){
                global_collapse_store[i]=collapse_int(arr[i]);
            }
            int global_collapse_addition=0;
            for(int i=0;i<new_n;i++){
                global_collapse_addition=global_collapse_addition+global_collapse_store[i];
            }
            int global_collapse=collapse_int(global_collapse_addition);
            printf("%d\n",global_collapse);
        }
        break;
 
}
    

    MPI_Finalize();
    return 0;
}