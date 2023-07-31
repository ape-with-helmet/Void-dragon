#include<stdio.h>
#include<stdlib.h>
void main()
{
    int i,j,rq[100],n,THM=0,init,size,move;
    printf("Enter no of requests: ");
    scanf("%d",&n);
    printf("Enter request sequence: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d",&rq[i]);
    }
    printf("Enter initial head position: ");
    scanf("%d",&init);
    printf("Enter disk size: ");
    scanf("%d",&size);
    printf("Enter the head movement direction for high 1 and for low 0: ");
    scanf("%d",&move);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n-i-1; j++)
        {
            if (rq[j]>rq[j+1])
            {
                int temp;
                temp=rq[j];
                rq[j]=rq[j+1];
                rq[j+1]=temp;
            }
        }
    }
    int index;
    for (i = 0; i < n; i++)
    {
        if (init<rq[i]) 
        {
            index=i;
            break;
        }
    }
    if (move==1)
    {
        printf("Sequence of request access: ");
        for (i = index; i < n; i++)
        {
            printf("%d ",rq[i]);
            THM=THM+abs(rq[i]-init);
            init=rq[i];
        }
        THM=THM+abs(size-rq[i-1]-1);
        init=size-1;
        for (i = index-1; i >= 0; i--)
        {
            printf("%d ",rq[i]);
            THM=THM+abs(rq[i]-init);
            init=rq[i];
        }
    }
    else
    {
        printf("Sequence of request access: \n");
        for (i = index; i >= 0; i--)
        {
           printf("%d ",rq[i]);
           THM=THM+abs(rq[i]-init);
           init=rq[i]; 
        }
        THM=THM+abs(rq[i+1]-0);
        init=0;
        for (i = index; i < n; i++)
        {
            printf("%d ",rq[i]);
            THM=THM+abs(rq[i]-init);
            init=rq[i];
        }
    }
    printf("\nTotal head movement is %d\n\n",THM);
}