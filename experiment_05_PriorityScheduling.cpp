#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id;         // Process ID
    int burstTime;  // CPU Burst time required
    int priority;   // Priority of this process
};

// Function to sort the processes according to priority
bool comparePriority(Process a, Process b) {
    return (a.priority > b.priority);
}

// Function to find the waiting time for all processes
void calculateWaitingTime(Process processes[], int n, int waitingTime[]) {
    waitingTime[0] = 0; // Waiting time for the first process is 0

    // Calculating waiting time
    for (int i = 1; i < n; i++)
        waitingTime[i] = processes[i - 1].burstTime + waitingTime[i - 1];
}

// Function to calculate turn around time
void calculateTurnAroundTime(Process processes[], int n, int waitingTime[], int turnAroundTime[]) {
    // Calculating turnaround time by adding burstTime[i] + waitingTime[i]
    for (int i = 0; i < n; i++)
        turnAroundTime[i] = processes[i].burstTime + waitingTime[i];
}

// Function to calculate average time
void calculateAvgTime(Process processes[], int n) {
    int waitingTime[n], turnAroundTime[n], totalWaitingTime = 0, totalTurnAroundTime = 0;

    // Function to find waiting time of all processes
    calculateWaitingTime(processes, n, waitingTime);

    // Function to find turn around time for all processes
    calculateTurnAroundTime(processes, n, waitingTime, turnAroundTime);

    // Display processes along with all details
    cout << "\nProcess ID | Burst Time | Waiting Time | Turnaround Time\n";
    
    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnAroundTime += turnAroundTime[i];
        cout << setw(10) << processes[i].id << setw(12) << processes[i].burstTime << setw(14) << waitingTime[i] << setw(17) << turnAroundTime[i] << endl;
    }

    // Calculate average waiting time and average turnaround time
    float avgWaitingTime = (float)totalWaitingTime / n;
    float avgTurnAroundTime = (float)totalTurnAroundTime / n;
    
    cout << "\nAverage Waiting Time: " << avgWaitingTime;
    cout << "\nAverage Turnaround Time: " << avgTurnAroundTime;
}

void priorityScheduling(Process processes[], int n) {
    // Sort processes by priority
    sort(processes, processes + n, comparePriority);

    // Display order of processes execution
    cout << "Order of process execution (by priority):\n";
    for (int i = 0; i < n; i++)
        cout << processes[i].id << " ";

    calculateAvgTime(processes, n);
}

int main() {
    Process processes[] = { { 1, 6, 3 }, { 2, 4, 1 }, { 3, 8, 2 } };
    int n = sizeof(processes) / sizeof(processes[0]);
    priorityScheduling(processes, n);
    return 0;
}
