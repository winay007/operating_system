#include "iostream"
#include "queue"
using namespace std;

struct pcb
{
    int pid, arrival_time, burst_time, completion_time, waiting_time, turnaround_time;
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

void performFCFS(struct pcb *processes[], int n)
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

   

    //actual scheduling
    int time = processes[0]->arrival_time;
    int total_wt = 0, total_tat = 0,completed = 0;

    while(completed < n){
        while(time < processes[completed]->arrival_time) time++;
        time  += processes[completed]->burst_time;
        processes[completed]->completion_time = time;
        processes[completed]->turnaround_time = time - processes[completed]->arrival_time;
        processes[completed]->waiting_time = processes[completed]->turnaround_time - processes[completed]->burst_time;
        total_tat += processes[completed]->turnaround_time;
        total_wt += processes[completed]->waiting_time;
        completed++;
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
    }
    performFCFS(processes, n);
    return 0;
}