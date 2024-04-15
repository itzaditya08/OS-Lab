#include <iostream>
using namespace std;

int main() {

	// Matrix for storing Process Id, Burst Time,
	// Waiting Time & Turnaround Time.
	int processes[100][4]; // [Process ID][0: Burst Time, 1: Waiting Time, 2: Turnaround Time]
	int i, j, numProcesses, totalWait = 0, index, temp;
	float avgWait, avgTurnaround;

	cout << "Enter number of processes: ";
	cin >> numProcesses;

	cout << "Enter Burst Time:" << endl;

	// User Input Burst Time and alloting Process Id.
	for (i = 0; i < numProcesses; i++) {
		cout << "Process " << i + 1 << ": ";
		cin >> processes[i][1]; // Taking Burst Time as input
		processes[i][0] = i + 1; // Assigning Process ID
	}

	// Sorting processes according to their Burst Time.
	for (i = 0; i < numProcesses; i++) {
		index = i;
		for (j = i + 1; j < numProcesses; j++)
			if (processes[j][1] < processes[index][1])
				index = j;
		// Swapping Burst Time and Process ID based on index
		temp = processes[i][1];
		processes[i][1] = processes[index][1];
		processes[index][1] = temp;

		temp = processes[i][0];
		processes[i][0] = processes[index][0];
		processes[index][0] = temp;
	}

	processes[0][2] = 0; // First process has zero waiting time
	// Calculation of Waiting Times
	for (i = 1; i < numProcesses; i++) {
		processes[i][2] = 0;
		for (j = 0; j < i; j++)
			processes[i][2] += processes[j][1]; // Summing Burst Times for waiting time
		totalWait += processes[i][2];
	}

	avgWait = (float)totalWait / numProcesses; // Average Waiting Time
	totalWait = 0;
	cout << "Process   Burst Time   Waiting Time   Turnaround Time" << endl;

	// Calculation of Turnaround Time and printing the data.
	for (i = 0; i < numProcesses; i++) {
		processes[i][3] = processes[i][1] + processes[i][2]; // Burst Time + Waiting Time = Turnaround Time
		totalWait += processes[i][3];
		cout << "P" << processes[i][0] << "         " << processes[i][1] << "           " << processes[i][2] << "                " << processes[i][3] << endl;
	}

	avgTurnaround = (float)totalWait / numProcesses; // Average Turnaround Time
	cout << "Average Waiting Time= " << avgWait << endl;
	cout << "Average Turnaround Time= " << avgTurnaround << endl;

	return 0;
}
