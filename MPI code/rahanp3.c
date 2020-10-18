#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include<math.h>

#define BUCKETSIZE 256

void printarr(int a[], int n, char *msg){
    int i;
	printf("\n%s\n", msg); 
    for(i = 0; i < n; i++){
	  printf("%3d ", a[i]); 
	  if ((i+1) % 10 == 0) printf("\n");
	}
    printf("\n");
 }

 void insertionSort(int *arr, int n) { 
	int i, j,tmp; 
	for (i = 1; i < n; i++) { 
		tmp = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > tmp) { 
			arr[j + 1] = arr[j]; 
			j = j - 1; 
		} 
		arr[j + 1] = tmp; 
	}	 
} 

void Bucket_Sort(int* array, int n,int a,int b,int p,int* sorted_array){   
    int bucket_index;
    int* item_counter;
    
    //create an array of buckets
    int **buckets=(int**) malloc(p * sizeof(int*));
    for(int i=0;i<p;i++){
        buckets[i]=(int*) malloc(BUCKETSIZE * sizeof(int));
    }
    //initialize all elements of buckets with zero
    for(int i=0; i<p; i++){
        for(int j=0;j<BUCKETSIZE;j++){
            buckets[i][j]=0;
        }
    }
    //item counter defines how many elements are in each bucket
    item_counter=(int*) malloc(p*sizeof(int));
    for(int i=0;i<p;i++){
        item_counter[i]=0;
    }
    //iterate through original array,and divide elements in respective buckets
    for(int i=0;i<n;i++){
        bucket_index=floor((p*array[i])/(b+1));
        // printf("%d ",bucket_index );
        int temp=item_counter[bucket_index];
        buckets[bucket_index][temp]=array[i];
        item_counter[bucket_index]=temp+1;
    }

    // sort each bucket using insertion sort and concat into sorted array
    int sorted_counter=0;
    for(int i=0; i<p; i++){
        int temp=item_counter[i];
        if (temp > 0){
        int* temparr=(int*)malloc(temp*sizeof(int));
        for(int j=0;j<temp;j++){
            temparr[j]=buckets[i][j];
        }
        // printf("Bucket no. %d",i);
        // printarr(temparr,temp,"Some array before sorting");
        insertionSort(temparr,temp);
        // printarr(temparr,temp,"Some array after sorting");
        for(int j=0;j<temp;j++){
            sorted_array[sorted_counter]=temparr[j];
            sorted_counter=sorted_counter+1;
        }
        }
    }

}   

int main(int argc, char* argv[])
{  

    int* arr,n,a,b,p,i;
    n= atoi(argv[1]);  // get n
    a= atoi(argv[2]);  // get a
    b= atoi(argv[3]);  // get b
    p= atoi(argv[4]);  // get p
    arr= (int*)malloc(n*sizeof(int));
    int* sortedarr=(int*)malloc(n*sizeof(int));
    FILE *inf;
    char *fname;
    fname = argv[5];  // get file name
    inf = fopen(fname,"r");// open finput file
    for(i = 0; i < n;i++)
        fscanf(inf, "%d", &arr[i]);
    fclose(inf);

    printarr(arr,n,"Before sorting");
    Bucket_Sort(arr, n,a,b,p,sortedarr); 
    printarr(sortedarr,n,"After sorting");   
    return 0;
}