#include "iostream"
#include "queue"
using namespace std;

struct pcb
{
    int pid, arrival_time, burst_time, completion_time, waiting_time, turnaround_time, rem_bt;
    pcb() {}
    pcb(int pid, int at, int bt)
    {
        this->pid = pid;
        this->arrival_time = at;
        this->burst_time = bt;
    }
};

void displayProcesses(struct pcb *processes[], int n)
{
    printf("Process\tBurst Time\tArrival Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i]->pid, processes[i]->burst_time, processes[i]->arrival_time,
               processes[i]->completion_time, processes[i]->turnaround_time, processes[i]->waiting_time);
    }
}

// with same arrival time
void roundRobin(struct pcb *processes[], int n, int quantum)
{
    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (processes[i]->rem_bt > 0)
            {
                int executeTime = (processes[i]->rem_bt < quantum) ? processes[i]->rem_bt : quantum;
                currentTime += executeTime;
                processes[i]->rem_bt -= executeTime;

                if (processes[i]->rem_bt == 0)
                {
                    completedProcesses++;
                    processes[i]->completion_time = currentTime;
                    processes[i]->turnaround_time = processes[i]->completion_time - processes[i]->arrival_time;
                    processes[i]->waiting_time = processes[i]->turnaround_time - processes[i]->burst_time;
                }
            }
        }
    }
}

void performRR(struct pcb *processes[], int n, int quantum)
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

    int at = processes[0]->arrival_time, i = 0;

    queue<pcb *> q;
    while (i < n && processes[i]->arrival_time == at)
        q.push(processes[i++]);

    // actual scheduling
    int time = at;
    int total_wt = 0, total_tat = 0;
    int completed = 0;

    while (!q.empty() || i < n)
    {
        pcb* curr = NULL;
        if (!q.empty())
        {
            curr = q.front();
            q.pop();
            time += (curr->rem_bt < quantum) ? curr->rem_bt : quantum;
            curr->rem_bt -= quantum;
            if (curr->rem_bt <= 0)
            {
                curr->completion_time = time;
                curr->turnaround_time = curr->completion_time - curr->arrival_time;
                curr->waiting_time = curr->turnaround_time - curr->burst_time;
                total_tat += curr->turnaround_time;
                total_wt += curr->waiting_time;
            }
        }else time++;

        while (i < n && processes[i]->arrival_time <= time)
            q.push(processes[i++]);

        if(curr && curr->rem_bt > 0) q.push(curr);
    }

    displayProcesses(processes, n);
    cout << "\nAverage waiting time: " << (float)total_wt / n << endl;
    cout << "Average turn around time: " << (float)total_tat / n << endl;
}

int main()
{
    int n, quantum;
    cout << "Enter the number of processes:";
    cin >> n;
    cout << "Enter the time quantum:";
    cin >> quantum;
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
    performRR(processes, n, quantum);
    return 0;
}