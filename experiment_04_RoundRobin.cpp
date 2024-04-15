#include<iostream> 
using namespace std; 

// Function to find the waiting time for all 
// processes 
void findWaitingTime(int processes[], int n, 
                     int burst_time[], int waiting_time[], int quantum) 
{ 
    // Make a copy of burst times burst_time[] to store remaining 
    // burst times. 
    int remaining_time[n]; 
    for (int i = 0; i < n ; i++) 
        remaining_time[i] = burst_time[i]; 

    int current_time = 0; // Current time 

    // Keep traversing processes in round robin manner 
    // until all of them are not done. 
    while (1) 
    { 
        bool done = true; 

        // Traverse all processes one by one repeatedly 
        for (int i = 0 ; i < n; i++) 
        { 
            // If remaining burst time of a process is greater than 0 
            // then only process further 
            if (remaining_time[i] > 0) 
            { 
                done = false; // There is a pending process 

                if (remaining_time[i] > quantum) 
                { 
                    // Increase the current_time by quantum 
                    current_time += quantum; 

                    // Decrease the remaining burst time of current process 
                    // by quantum 
                    remaining_time[i] -= quantum; 
                } 
                else
                { 
                    // Increase the current_time by remaining time 
                    current_time = current_time + remaining_time[i]; 

                    // Waiting time is current time minus burst time 
                    waiting_time[i] = current_time - burst_time[i]; 

                    // As the process gets fully executed 
                    // make its remaining burst time = 0 
                    remaining_time[i] = 0; 
                } 
            } 
        } 

        // If all processes are done 
        if (done == true) 
            break; 
    } 
} 

// Function to calculate turn around time 
void findTurnAroundTime(int processes[], int n, 
                        int burst_time[], int waiting_time[], int turn_around_time[]) 
{ 
    // calculating turnaround time by adding 
    // burst_time[i] + waiting_time[i] 
    for (int i = 0; i < n ; i++) 
        turn_around_time[i] = burst_time[i] + waiting_time[i]; 
} 

// Function to calculate average time 
void findAverageTime(int processes[], int n, int burst_time[], 
                     int quantum) 
{ 
    int waiting_time[n], turn_around_time[n], total_waiting_time = 0, total_turn_around_time = 0; 

    // Function to find waiting time of all processes 
    findWaitingTime(processes, n, burst_time, waiting_time, quantum); 

    // Function to find turn around time for all processes 
    findTurnAroundTime(processes, n, burst_time, waiting_time, turn_around_time); 

    // Display processes along with all details 
    cout << "Process\tBurst Time\tWaiting Time\tTurnaround Time\n"; 

    // Calculate total waiting time and total turn around time 
    for (int i = 0; i < n; i++) 
    { 
        total_waiting_time = total_waiting_time + waiting_time[i]; 
        total_turn_around_time = total_turn_around_time + turn_around_time[i]; 
        cout << "P" << processes[i] << "\t\t" << burst_time[i] << "\t\t" << waiting_time[i] << "\t\t" << turn_around_time[i] << endl; 
    } 

    // Calculate and display average waiting time and average turn around time 
    cout << "\nAverage Waiting Time = " << (float)total_waiting_time / (float)n; 
    cout << "\nAverage Turnaround Time = " << (float)total_turn_around_time / (float)n; 
} 

// Driver code 
int main() 
{ 
    // Process IDs 
    int processes[] = { 1, 2, 3, 4}; 
    int n = sizeof processes / sizeof processes[0]; 

    // Burst time of all processes 
    int burst_time[] = {8, 5, 10, 3}; 

    // Time quantum 
    int quantum = 2; 

    // Call the function to calculate average time 
    findAverageTime(processes, n, burst_time, quantum); 

    return 0; 
} 
