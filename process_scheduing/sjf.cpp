#include "iostream"
#include "queue"
using namespace std;

struct pcb
{
    int pid, arrival_time, burst_time, completion_time, waiting_time, turnaround_time,rem_bt;
    pcb() {}
    pcb(int pid, int at, int bt)
    {
        this->pid = pid;
        this->arrival_time = at;
        this->burst_time = bt;
    }
};


void displayProcesses(struct pcb *processes[], int n) {
    printf("Process\tBurst Time\tArrival Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i]->pid, processes[i]->burst_time, processes[i]->arrival_time,
            processes[i]->completion_time, processes[i]->turnaround_time, processes[i]->waiting_time);
    }
}

//with PQ
// void performSJF(struct pcb *processes[], int n)
// {
//     // sort the processes based on arrival time
//     for (int i = 0; i < n; i++)
//     {
//         int min = i;
//         struct pcb *temp;
//         for (int j = i; j < n; j++)
//             if (processes[min]->arrival_time > processes[j]->arrival_time)
//                 min = j;
//         temp = processes[min];
//         processes[min] = processes[i];
//         processes[i] = temp;
//     }

//     // for (int i = 0; i < n; i++)
//     //     cout << processes[i]->pid << " " << processes[i]->arrival_time << endl;

//     priority_queue<pair<int, pcb *>, vector<pair<int, pcb *>>, greater<pair<int, pcb *>>> pq;
//     int at = processes[0]->arrival_time, i = 0;
//     while (i < n && at == processes[i]->arrival_time)
//     {
//         pq.push({processes[i]->burst_time, processes[i]});
//         i++;
//     }

//     //actual scheduling
//     int time = at;
//     int total_wt = 0, total_tat = 0;

//     while (!pq.empty())
//     {
//        pcb* curr = pq.top().second;
//        pq.pop();
       
//        int ct =  time + curr->burst_time;
//        curr->completion_time = ct;
//        curr->turnaround_time = ct - curr->arrival_time;
//        curr->waiting_time = curr->turnaround_time - curr->burst_time;
//        total_tat += curr->turnaround_time;
//        total_wt += curr->waiting_time;

//        while(i < n && processes[i]->arrival_time <= ct){
//             pq.push({processes[i]->burst_time,processes[i]});
//             i++;
//        }   
//        time = ct;
//     }

//     displayProcesses(processes,n);
//     cout<<"\nAverage waiting time: "<<(float) total_wt/n<<endl;
//     cout<<"Average turn around time: "<<(float)total_tat/n<<endl;
//  }

//without PQ
 void performSJF(struct pcb *processes[], int n)
{
    // sort the processes based on arrival time
    for (int i = 0; i < n; i++)
    {
        int min = i;
        struct pcb *temp;
        for (int j = i; j < n; j++)
            if (processes[min]->arrival_time > processes[j]->arrival_time)
                min = j;
        temp = processes[min];
        processes[min] = processes[i];
        processes[i] = temp;
    }

    // for (int i = 0; i < n; i++)
    //     cout << processes[i]->pid << " " << processes[i]->arrival_time << endl;


    int at = processes[0]->arrival_time;

    //actual scheduling
    int time = at;
    int total_wt = 0, total_tat = 0;
    int completed = 0;


    while (completed != n)
    {
       int j = 0,min_burst = 1000,min_idx = -1;
       while(j < n && processes[j]->arrival_time <= time){
            if(processes[j]->burst_time < min_burst && processes[j]->rem_bt > 0){
                min_burst = processes[j]->burst_time;
                min_idx = j;
            }
            j++;
       }

       if(min_idx == -1) time++;
       else{
          completed++;
          time += min_burst;
          processes[min_idx]->completion_time = time;
          processes[min_idx]->turnaround_time = processes[min_idx]->completion_time - processes[min_idx]->arrival_time;
          processes[min_idx]->waiting_time = processes[min_idx]->turnaround_time - processes[min_idx]->burst_time;
          total_wt+=processes[min_idx]->waiting_time;
          total_tat += processes[min_idx]->turnaround_time;
          processes[min_idx]->rem_bt = 0;
       }
    }

    displayProcesses(processes,n);
    cout<<"\nAverage waiting time: "<<(float) total_wt/n<<endl;
    cout<<"Average turn around time: "<<(float)total_tat/n<<endl;
 }



int main()
{
    int n;
    cout << "Enter the number of processes:";
    cin >> n;
    struct pcb *processes[n];
    for (int i = 0; i < n; i++)
    {
        processes[i] = new pcb();
        processes[i]->pid = i + 1;
        cout << "\nProcess " << i + 1 << ":\nPID: ";
        cout << "Enter the arrival time:";
        cin >> processes[i]->arrival_time;
        cout << "Enter the burst time:";
        cin >> processes[i]->burst_time;
        processes[i]->rem_bt = processes[i]->burst_time;
    }
    performSJF(processes, n);
    return 0;
}