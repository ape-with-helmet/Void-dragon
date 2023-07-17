#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#define NUM_PHILOSOPHERS 5
#define NUM_CHOPSTICKS 5

void dine(int n);
pthread_t
philosopher[NUM_PHILOSOPHERS];
pthread_mutex_t
chopstick[NUM_CHOPSTICKS];
void main()
{
    int i,status_message;
    void *msg;
    for (int i = 1; i <= NUM_CHOPSTICKS; i++)
    {
        status_message=pthread_mutex_init(&chopstick[i],NULL);
        if (status_message==-1)
        {
            printf("\nMutex initialization failed\n");
            exit(1);
        }
    }
    for (int i = 1; i <= NUM_PHILOSOPHERS; i++)
    {
        status_message=pthread_create(&philosopher[i],NULL,(void *)dine,(int *)i);
        if (status_message!=0)
        {
            printf("\nThread creation error\n");
            exit(1);
        }
    }
}