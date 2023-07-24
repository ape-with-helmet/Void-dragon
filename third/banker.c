#include<stdio.h>
#include<stdlib.h>
//#include<conio.h>
void main()
{
    int k=0,op[10],a=0,b=0,instance[5],availability[5],allocated[10][5],need[10][5],MAX[10][5],process,P[10],no_of_resources,cnt=0,i,j;
    printf("\nEnter the no of resources: ");
    scanf("%d",&no_of_resources);
    printf("\nEnter the max instances of each resources\n");
    for (int i = 0; i < no_of_resources; i++)
    {
        availability[i]=0;
        printf("%c=",(i+97));
        scanf("%d",&instance[i]);
    }
    printf("\nEnter the no of processes: ");
    scanf("%d",&process);
    printf("Enter the allocation matrix\n");
    printf("\ta b c\n");
    for (int i = 0; i < process; i++)
    {
        P[i]=i;
        printf("P[%d] ",P[i]);
        for (int j = 0; j < no_of_resources; j++)
        {
            scanf("%d",&allocated[i][j]);
            availability[j]+=allocated[i][j];
        }
    }
    printf("\nEnter the MAX matrix\n");
    for (int i = 0; i < no_of_resources; i++)
    {
        printf("%c",(i+97));
        availability[i]=instance[i]-availability[i];
    }
    printf("\n");
    for (int i = 0; i < process; i++)
    {
        cnt=0;
        b=P[i];
        printf("P[%d] ",i);
        for (int j = 0; j < no_of_resources; j++)
        {
            scanf("%d",&MAX[i][j]);
        }
    }
    printf("\n");
    A: a=-1;
    for (int i = 0; i < process; i++)
    {
        cnt=0;
        b=P[i];
        for (int j = 0; j < no_of_resources; j++)
        {
            need[b][j]=MAX[b][j]-allocated[b][j];
            if (need[b][j]<=availability[j])
            {
                cnt++;
            }
        }
        if (cnt==no_of_resources)
        {
            op[k++]=P[i];
            for (int j = 0; j < no_of_resources; j++)
            {
                availability[j]+=allocated[b][j];
            }
        }
        else
        {
            P[++a]=P[i];
        }
    }
    if(a!=-1)
    {
        process=a+1;
        goto A;
    }
    printf("\t<");
    for (int i = 0; i < k; i++)
    {
        printf("P[%d] ",op[i]);
        printf(">");
    }
    getchar();
}