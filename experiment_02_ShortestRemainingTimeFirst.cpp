#include <bits/stdc++.h>
using namespace std;

struct Process {
    int pid; // Process ID
    int burstTime; // Burst Time
    int arrivalTime; // Arrival Time
};

// Function to find Waiting Time of each process
void findWaitingTime(Process proc[], int n, int wt[]) {
    int remainingTime[n];

    // Copy the burst time into remainingTime[]
    for (int i = 0; i < n; i++)
        remainingTime[i] = proc[i].burstTime;

    int complete = 0, currentTime = 0, shortest = 0, finishTime;
    bool check = false;

    // Process until all processes get completed
    while (complete != n) {
        // Find process with minimum remaining time
        for (int j = 0; j < n; j++) {
            if ((proc[j].arrivalTime <= currentTime) && (remainingTime[j] < remainingTime[shortest]) && (remainingTime[j] > 0)) {
                shortest = j;
                check = true;
            }
        }

        if (!check) {
            currentTime++;
            continue;
        }

        // Reduce remaining time by one unit
        remainingTime[shortest]--;

        // If a process gets completely executed
        if (remainingTime[shortest] == 0) {
            complete++;
            check = false;

            // Find finish time of current process
            finishTime = currentTime + 1;

            // Calculate waiting time
            wt[shortest] = finishTime - proc[shortest].burstTime - proc[shortest].arrivalTime;
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }

        // Increment current time
        currentTime++;
    }
}

// Function to find Turnaround Time of each process
void findTurnAroundTime(Process proc[], int n, int wt[], int tat[]) {
    // Calculate turnaround time by adding burstTime and waitingTime
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].burstTime + wt[i];
}

// Function to calculate average time
void findAverageTime(Process proc[], int n) {
    int waitingTime[n], turnaroundTime[n], totalWaitingTime = 0, totalTurnaroundTime = 0;
    findWaitingTime(proc, n, waitingTime);
    findTurnAroundTime(proc, n, waitingTime, turnaroundTime);

    cout << "P\tBT\tWT\tTAT\n";
    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
        cout << proc[i].pid << "\t" << proc[i].burstTime << "\t" << waitingTime[i] << "\t" << turnaroundTime[i] << endl;
    }

    cout << "\nAverage Waiting Time = " << (float)totalWaitingTime / n;
    cout << "\nAverage Turnaround Time = " << (float)totalTurnaroundTime / n;
}

int main() {
    Process proc[] = { { 1, 6, 2 }, { 2, 2, 5 },{ 3, 8, 1 }, { 4, 3, 0}, {5, 4, 4} };
    int n = sizeof(proc) / sizeof(proc[0]);
    findAverageTime(proc, n);
    return 0;
}
