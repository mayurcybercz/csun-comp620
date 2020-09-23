#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* matrix1 ( m*n) and matrix2 (n*p) */

void printMatrix(int **matrix,int row,int col){
    for(int i=0; i<row; i++){
        for(int j=0;j<col;j++){
            printf("%d\t",matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void genMatrix(int **matrix,int row,int col, int range1,int range2){
    int range= range2-range1+1;

    for(int i=0; i<row; i++){
        for(int j=0;j<col;j++){
            matrix[i][j]=(rand()%range)+range1;
        }
    }

}

void zeroMatrix(int **matrix,int row,int col){
    for(int i=0; i<row; i++){
        for(int j=0;j<col;j++){
            matrix[i][j]=0;
        }
    }
}

void matrixMul(int **matrix1,int **matrix2,int **res_mat,int row1, int col1, int col2){
    /*col1 = row2 */
    for(int i=0;i<row1;i++){
        for(int j=0;j<col2;j++){
            for(int k=0;k<col1;k++){
                res_mat[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

}


int main() {
    int m=2;
    int n=2;
    int p=2;
    int a=10;
    int b=200;

    int **mat1=(int**) malloc(m * sizeof(int*));
    for(int i=0;i<m;i++){
        mat1[i]=(int*) malloc(n * sizeof(int));
    }

    int **mat2=(int**) malloc(n * sizeof(int*));
    for(int i=0;i<n;i++){
        mat2[i]=(int*) malloc(p * sizeof(int));
    }

    int **result=(int**) malloc(m * sizeof(int*));
    for(int i=0;i<m;i++){
        result[i]=(int*) malloc(p * sizeof(int));
    }
    
    srand(time(0)); /*current time*/
   
    genMatrix(mat1,m,n,a,b);
    genMatrix(mat2,n,p,a,b);
    zeroMatrix(result,m,p);
    printMatrix(mat1,m,n);
    printMatrix(mat2,n,p);
    matrixMul(mat1,mat2,result,m,n,p);



    printMatrix(result,m,p);



    return 0;
}