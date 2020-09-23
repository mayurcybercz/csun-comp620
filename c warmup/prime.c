#include <stdio.h>  
int main() 
{ 
    int m=100;
    int n=1234;
    int isPrime;
    int prettyPrint=0;
    int counter=0;
    
    for (int i = m; i <= n; i++) {       
        if (i == 1 || i == 0) 
            continue;  
        isPrime=1;
        for (int j = 2; j <= i / 2; ++j) { 
            if (i % j == 0) { 
                isPrime = 0; 
                break; 
            } 
        }        
        if (isPrime == 1){
            counter+=1;
            printf("%d ", i); 
            prettyPrint+=1;
            if(prettyPrint%10==0){
            printf("\n");
            }
        }
    } 
    printf(" \nTotal primes are %d \n",counter);  
    return 0; 
} 