#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int row=3;
    int col=3;
    int a= 10;
    int b = 20;
    int range = b-a+1;

    time_t t1;
	time(&t1);
	srand(t1);

    int **mat=(int**) malloc(row * sizeof(int*));
    for(int i=0;i<row;i++){
        mat[i]=(int*) malloc(col * sizeof(int));
    }

    for(int i=0; i<row; i++){
        for(int j=0;j<col;j++){
            mat[i][j]= (rand() % range) + a;
        }
    }

    for(int i=0; i<row; i++){
        for(int j=0;j<col;j++){
            printf("%d\t",mat[i][j]);
        }
        printf("\n");
    }

    return 0;
}