#include<stdio.h>
#define MAX 200
int main()
{
    int res[MAX],fac_len,carry;
    int prettyPrint=0;
    int k=20;
    res[0]=1;
    fac_len=0;
    int n=100;
    for(; n>=2; n--)
    {
        carry=0;
        for(int i=0; i<=fac_len; i++)
        {
            carry=(res[i]*n)+carry;
            res[i]=carry%10;
            carry=carry/10;
        }
        while(carry>0)
        {
            res[++fac_len]=carry%10;
            carry=carry/10;
        }
    }
    
    for(int i=fac_len; i>=0; i--){
        
        if(prettyPrint%k==0){
            printf("\n");
            printf("%d",res[i]);
        }
        else{
            printf("%d",res[i]);
        }
        prettyPrint+=1;
        

    }
    printf("\n");
    return 0;
}