#include<stdio.h>
#include<stdlib.h>
void main()
{
    int i,n,req[50],mov=0,cp;
    printf("Enter the current position: ");
    scanf("%d",&cp);
    printf("Enter the no of requests: ");
    scanf("%d",&n);
    printf("Enter the request order: ");
    for (int i = 0; i < n; i++)
        scanf("%d",&cp);
    mov=mov+abs(cp-req[0]);
    
}