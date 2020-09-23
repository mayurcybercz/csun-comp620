#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


void genArray(int *arr, int n, int range1, int range2) {
	int i, range = range2 - range1 + 1;
	time_t t1;
	time(&t1);
	srand(t1);

	for (i = 0; i < n; i++) {
		arr[i] = (rand() % range) + range1;
	}
}

void printArray(int *arr, int n, int k) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%7d ", arr[i]);
		if ((i + 1) % k == 0) printf("\n");
	}
	printf("\n");
}

/*code for bubble sort starts*/

void bubblesort(int* arr, int n) {
	int i, j;
	for (i = 1; i < n; i++) {
		for (j = 0; j < n-i; j++) {
			if (arr[j] > arr[j + 1]) {
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}

/*code for bubble sort ends */

/*code for insertion sort starts*/
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
/*code for insertion sort ends */

/*code for selection sort starts*/
/*code for selection sort ends */

/*code for quick sort starts*/

void swapElements(int* x, int* y) { 
	int temp = *x; 
	*x = *y; 
	*y = temp; 
}   

int partition (int arr[], int lowIndex, int highIndex) { 
	int pivotElement = arr[highIndex];
	int i = (lowIndex - 1); 
	for (int j = lowIndex; j <= highIndex- 1; j++) { 
		if (arr[j] <= pivotElement) { 
			i++; 
			swapElements(&arr[i], &arr[j]); 
		} 
	} 
	swapElements(&arr[i + 1], &arr[highIndex]); 
	return (i + 1); 
}   

void quickSort(int *arr, int lowIndex, int highIndex) { 
	if (lowIndex < highIndex) { 
		int pivot = partition(arr, lowIndex, highIndex); 
 		quickSort(arr, lowIndex, pivot - 1); 
		quickSort(arr, pivot + 1, highIndex); 
	} 
}   

/*code for quick sort ends */

/*code for merge sort starts*/
/*code for merge sort ends */

/*code for heap sort starts*/
/*code for heap sort ends */


int main(int argc,char *argv[]) {
	int* arr,n, k, a, b;
	n = atoi(argv[1]);
	k = atoi(argv[2]);
	a = atoi(argv[3]);
	b = atoi(argv[4]);

	arr = malloc((n) * sizeof(int));
	genArray(arr, n, a, b);
	printArray(arr, n, k);

    /* time() returns epoch time only in seconds but 
        gettimeofday() returns epoch time in seconds and microseconds
        so, using both the methods below */

    struct timeval begin, end;
    gettimeofday(&begin, 0);
	
	time_t ts,te;

	time(&ts);
	printf("\n Starting time = %ld \n", ts);
	
	bubblesort(arr, n);
	/*
	insertionSort(arr,n);
	
	quickSort(arr,0,n-1);
*/
	time(&te);
    printf("\n Ending time = %ld \n", te);

    printArray(arr, n, k);


    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;

	printf("\nExecution time measured with time() = %ld \n",te-ts);
    printf("Execution time measured measured with gettimeofday(): %.3f seconds.\n", elapsed);

	
	free(arr);

	return 0;
	
}