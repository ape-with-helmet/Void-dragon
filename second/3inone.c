#include<stdio.h>
void printer(int processes[],int n,int burst_time[],int arrival_time[],int priority[])
{
    int WT[n],TAT[n],total_WT=0,total_TAT=0,completion_time[n],idle=0,RT[n];
    for (int i = 0; i < n; i++)//calculating times
    {
        if(i==0)
        {
            WT[0]=0;
            completion_time[0]=burst_time[0]+arrival_time[0];
            TAT[0]=completion_time[0]-arrival_time[0];
            total_TAT=TAT[0];
            RT[0]=0;
            if(arrival_time[0]!=0)
            {
                idle=arrival_time[0];
            }
            continue;
        }
        if(completion_time[i-1]<arrival_time[i])
        {
            completion_time[i]=arrival_time[i]+burst_time[i];
            idle+=(arrival_time[i]-completion_time[i-1]);
            RT[i]=0;
        }
        else
        {
            completion_time[i]=completion_time[i-1]+burst_time[i];
            RT[i]=completion_time[i-1]-arrival_time[i];
        }
        TAT[i]=completion_time[i]-arrival_time[i];
        total_TAT+=TAT[i];
        WT[i]=TAT[i]-burst_time[i];
        total_WT+=WT[i];
    }
    printf("Processes\tAT\tBT\tPriority\tWT\tTAT\tCT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n",processes[i],arrival_time[i],burst_time[i],priority[i],WT[i],TAT[i],completion_time[i],RT[i]);
    }
    printf("AVG waiting time: %2f\n",(float)total_WT/n);
    printf("AVG turnaround time: %2f\n",(float)total_TAT/n);
    printf("Total Idle time: %d\n",idle);
    printf("\n");
}
void Sorter(int priority[],int n,int processes[],int burst_time[],int arrival_time[],int key)
{
    for (int i = 0; i < n; i++)//sorting in priority
    {
        int first=i;
        switch (key)
        {
        case 1:
            for (int j = i+1; j < n; j++)
            {
                if (arrival_time[j]<arrival_time[first])
                {
                    first=j;
                }
            }
            break;
        case 2:
            for (int j = i+1; j < n; j++)
            {
                if (burst_time[j]<burst_time[first])
                {
                    first=j;
                }
            }
            break;
        case 3:
            for (int j = i+1; j < n; j++)
            {
                if (priority[j]>priority[first])
                {
                    first=j;
                }
            }
            break;
        default:
            break;
        }
        int temp=priority[i];
        priority[i]=priority[first];
        priority[first]=temp;
        
        temp=processes[i];
        processes[i]=processes[first];
        processes[first]=temp;

        temp=burst_time[i];
        burst_time[i]=burst_time[first];
        burst_time[first]=temp;

        temp=arrival_time[i];
        arrival_time[i]=arrival_time[first];
        arrival_time[first]=temp;
    }
}
void fcfs(int processes[],int n,int burst_time[],int arrival_time[],int priority[])
{
    Sorter(priority,n,processes,burst_time,arrival_time,1);
    printf("FCFS agorithm\n");
    printer(processes,n,burst_time,arrival_time,priority);
}
void sjf(int processes[],int n,int burst_time[],int arrival_time[],int priority[])
{
    Sorter(priority,n,processes,burst_time,arrival_time,2);
    printf("SJF agorithm\n");
    printer(processes,n,burst_time,arrival_time,priority);
}
void priority(int processes[],int n,int burst_time[],int arrival_time[],int priority[])
{
    int remaining_time[n],WT[n],TAT[n],total_WT=0,total_TAT=0,time=0,RT[n],flag[n],avg_RT=0;
    int completion_time[n];
    int all_processes_completed[n],idle=0;
    Sorter(priority,n,processes,burst_time,arrival_time,3);
    for (int i = 0; i < n; i++)//setting remaining time
    {
        remaining_time[i]=burst_time[i];
        RT[i]=0;
        flag[i]=0;
        completion_time[n]=0;
        all_processes_completed[i]=1;
    }
    while(1)
    {
        int x=time,check=0;
        for (int i = 0; i < n; i++)
        {
            if (remaining_time[i]>0&&arrival_time[i]<=time)//non-preemption process
            {
                if(flag[i]==0){
                    flag[i]=1;
                    RT[i]=time-arrival_time[i];
                    avg_RT+=RT[i];
                }
                time+=remaining_time[i];
                completion_time[i]=time;
                remaining_time[i]=0;
                all_processes_completed[i]=0;
            }
        }
        for (int i = 0; i < n; i++)//checking if all processes have finished executing
        {
            check+=all_processes_completed[i];
        }
        if (time==x&&check!=0)//checking for idle times
        {
            time++;
            idle++;
        }
        if (check==0)break;  
    }
    for (int i = 0; i < n; i++)//calculating times
    {
        TAT[i]=completion_time[i]-arrival_time[i];
        total_TAT+=TAT[i];
        WT[i]=TAT[i]-burst_time[i];
        total_WT+=WT[i];
    }
    printf("\nPriority algorithm\n");
    printf("Processes\tAT\tBT\tPriority\tWT\tTAT\tCT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n",processes[i],arrival_time[i],burst_time[i],priority[i],WT[i],TAT[i],completion_time[i],RT[i]);
    }
    printf("AVG waiting time: %2f\n",(float)total_WT/n);
    printf("AVG turnaround time: %2f\n",(float)total_TAT/n);
    printf("AVG Response time: %2f\n",(float)avg_RT/n);
    printf("Total Idle time: %d\n",idle);
    printf("\n");
}
void roundRobin(int processes[],int n,int burst_time[],int quantum,int arrival_time[],int priority[])
{
    int remaining_time[n],WT[n],TAT[n],total_WT=0,total_TAT=0,time=0,RT[n],flag[n],avg_RT=0;
    int completion_time[n];
    int all_processes_completed[n],idle=0;
    Sorter(priority,n,processes,burst_time,arrival_time,3);
    for (int i = 0; i < n; i++)//setting remaining time
    {
        remaining_time[i]=burst_time[i];
        RT[i]=0;
        flag[i]=0;
        completion_time[n]=0;
        all_processes_completed[i]=1;
    }
    while(1)
    {
        int x=time,check=0;
        for (int i = 0; i < n; i++)
        {
            if (remaining_time[i]>0&&arrival_time[i]<=time)//preemption process
            {
                if(flag[i]==0){
                    flag[i]=1;
                    RT[i]=time-arrival_time[i];
                    avg_RT+=RT[i];
                }
                if (remaining_time[i]>quantum)
                {
                    remaining_time[i]-=quantum;
                    time+=quantum;
                }
                else
                {
                    time+=remaining_time[i];
                    completion_time[i]=time;
                    remaining_time[i]=0;
                    all_processes_completed[i]=0;
                }
            }
        }
        for (int i = 0; i < n; i++)//checking if all processes have finished executing
        {
            check+=all_processes_completed[i];
        }
        if (time==x&&check!=0)//checking for idle times
        {
            time++;
            idle++;
        }
        if (check==0)break;
        
    }
    for (int i = 0; i < n; i++)//calculating times
    {
        TAT[i]=completion_time[i]-arrival_time[i];
        total_TAT+=TAT[i];
        WT[i]=TAT[i]-burst_time[i];
        total_WT+=WT[i];
    }
    printf("\nROund RObin algorithm\n");
    printf("Processes\tAT\tBT\tPriority\tWT\tTAT\tCT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n",processes[i],arrival_time[i],burst_time[i],priority[i],WT[i],TAT[i],completion_time[i],RT[i]);
    }
    printf("AVG waiting time: %2f\n",(float)total_WT/n);
    printf("AVG turnaround time: %2f\n",(float)total_TAT/n);
    printf("AVG Response time: %2f\n",(float)avg_RT/n);
    printf("Total Idle time: %d\n",idle);
    printf("\n");
}
void main()
{
    int n=4;
    int quantum;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    int processes[n],burst_time[n],arrival_time[n],prioritylist[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter the arrival time for process %d:",i+1);
        scanf("%d",&arrival_time[i]);
        printf("Enter the Burst time for processes %d:",i+1);
        scanf("%d",&burst_time[i]);
        printf("Enter the priority for process %d:",i+1);
        scanf("%d",&prioritylist[i]);
        processes[i]=i+1;
    }
    printf("Enter the time quantum for round robin: ");
    scanf("%d",&quantum);
    fcfs(processes,n,burst_time,arrival_time,prioritylist);
    sjf(processes,n,burst_time,arrival_time,prioritylist);
    priority(processes,n,burst_time,arrival_time,prioritylist);
    roundRobin(processes,n,burst_time,quantum,arrival_time,prioritylist);
}
//output
/*
Enter the number of processes: 4
Enter the arrival time for process 1:2
Enter the Burst time for processes 1:1
Enter the priority for process 1:1
Enter the arrival time for process 2:1
Enter the Burst time for processes 2:5
Enter the priority for process 2:1
Enter the arrival time for process 3:4
Enter the Burst time for processes 3:1
Enter the priority for process 3:1
Enter the arrival time for process 4:0
Enter the Burst time for processes 4:6
Enter the priority for process 4:1
Enter the time quantum for round robin: 2
FCFS agorithm
Processes       AT      BT      Priority        WT      TAT     CT      RT
4               0       6       1               0       6       6       0
2               1       5       1               5       10      11      5
1               2       1       1               9       10      12      9
3               4       1       1               8       9       13      8
AVG waiting time: 5.500000
AVG turnaround time: 8.750000
Total Idle time: 0

SJF agorithm
Processes       AT      BT      Priority        WT      TAT     CT      RT
1               2       1       1               0       1       3       0
3               4       1       1               0       1       5       0
2               1       5       1               4       9       10      4
4               0       6       1               10      16      16      10
AVG waiting time: 3.500000
AVG turnaround time: 6.750000
Total Idle time: 3


Priority algorithm
Processes       AT      BT      Priority        WT      TAT     CT      RT
1               2       1       1               4       5       7       4
3               4       1       1               3       4       8       3
2               1       5       1               7       12      13      7
4               0       6       1               0       6       6       0
AVG waiting time: 3.500000
AVG turnaround time: 6.750000
AVG Response time: 3.500000
Total Idle time: 0


ROund RObin algorithm
Processes       AT      BT      Priority        WT      TAT     CT      RT
1               2       1       1               0       1       3       0
3               4       1       1               3       4       8       3
2               1       5       1               7       12      13      2
4               0       6       1               6       12      12      0
AVG waiting time: 4.000000
AVG turnaround time: 7.250000
AVG Response time: 1.250000
Total Idle time: 0

*/