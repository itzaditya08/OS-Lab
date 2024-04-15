#include <iostream>
#include <vector>

using namespace std;

// Define a struct for each process with relevant attributes
struct Process {
    int id; // Process ID
    int arrivalTime; // Arrival Time of the process
    int burstTime; // Burst Time required by the process
    int completionTime; // Time at which process completes execution
    int turnaroundTime; // Turnaround Time for the process
    int waitingTime; // Waiting Time for the process
};

// Function to perform First Come First Serve (FCFS) scheduling
void fcfs(vector<Process> processes, int n) {
    int time = 0, count = 0;
    vector<int> completionTime(n), turnaroundTime(n), waitingTime(n);

    // Loop until all processes are completed
    while (count < n) {
        // Check if any process has arrived at the current time
        if (processes[count].arrivalTime == time) {
            time += processes[count].burstTime; // Increment time by burst time of the process
            completionTime[count] = time; // Set completion time for the process
            count++; // Move to the next process
        } else {
            time++; // Increment time if no process arrived
        }
    }

    // Calculate turnaround time and waiting time for each process
    time = 0;
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = completionTime[i] - processes[i].arrivalTime;
        waitingTime[i] = turnaroundTime[i] - processes[i].burstTime;
        time += processes[i].burstTime;
    }

    // Display the schedule and process details
    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t\t" << processes[i].arrivalTime << "\t\t" << processes[i].burstTime << "\t\t" << processes[i].completionTime << "\t\t" << processes[i].turnaroundTime << "\t\t" << processes[i].waitingTime << endl;
    }

    // Calculate and display average waiting time and average turnaround time
    float avgWaitingTime = 0, avgTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        avgWaitingTime += waitingTime[i];
        avgTurnaroundTime += turnaroundTime[i];
    }

    cout << "Average Waiting Time: " << avgWaitingTime / n << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime / n << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter details for process " << i + 1 << endl;
        cout << "Arrival time: ";
        cin >> processes[i].arrivalTime;
        cout << "Burst time: ";
        cin >> processes[i].burstTime;
        processes[i].id = i + 1;
        processes[i].completionTime = 0;
        processes[i].turnaroundTime = 0;
        processes[i].waitingTime = 0;
    }

    // Call the FCFS scheduling function
    fcfs(processes, n);

    return 0;
}
