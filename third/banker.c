#include<stdio.h>
//#include<conio.h>
void main()
{
    int k=0,a=0,b=0,instance[5],availability[5],allocated[10][5],need[10][5],MAX[10][5],process,P[10],no_of_resources,cnt=0,i,j;
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
    for (int i = 0; i < no_of_resources; i++)
    {
        printf("%c\n",(i+97));
    }
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
}