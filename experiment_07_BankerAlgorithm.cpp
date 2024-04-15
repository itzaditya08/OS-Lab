#include <iostream>
using namespace std;

// Define constants for number of processes and resources
const int NUM_PROCESSES = 3;
const int NUM_RESOURCES = 4;

// Function to check if the system is in a safe state
bool isSafeState(int allocation[NUM_PROCESSES][NUM_RESOURCES],
                 int max[NUM_PROCESSES][NUM_RESOURCES],
                 int need[NUM_PROCESSES][NUM_RESOURCES],
                 int available[NUM_RESOURCES]) {
    int work[NUM_RESOURCES], finish[NUM_PROCESSES];

    // Initialize work and finish arrays
    for (int i = 0; i < NUM_RESOURCES; i++)
        work[i] = available[i];
    for (int i = 0; i < NUM_PROCESSES; i++)
        finish[i] = 0;

    // Find an index i such that both conditions are satisfied
    int count = 0;
    while (count < NUM_PROCESSES) {
        bool found = false;
        for (int i = 0; i < NUM_PROCESSES; i++) {
            if (finish[i] == 0) {
                int j;
                found = true;
                for (j = 0; j < NUM_RESOURCES; j++)
                    if (need[i][j] > work[j])
                        break;
                if (j == NUM_RESOURCES) {
                    for (j = 0; j < NUM_RESOURCES; j++)
                        work[j] += allocation[i][j];
                    finish[i] = 1;
                    count++;
                }
            }
        }

        // If no process can be executed, the system is in an unsafe state
        if (!found)
            return false;
    }

    // If all processes have been executed, the system is in a safe state
    return true;
}

int main() {
    // Define the allocation, max, and available arrays with a different input
    int allocation[NUM_PROCESSES][NUM_RESOURCES] = { { 0, 1, 1, 0 },
                                                      { 2, 0, 0, 1 },
                                                      { 3, 0, 1, 0 } };
    int max[NUM_PROCESSES][NUM_RESOURCES] = { { 1, 2, 1, 0 },
                                               { 3, 0, 2, 1 },
                                               { 4, 0, 2, 2 } };
    int need[NUM_PROCESSES][NUM_RESOURCES];
    int available[NUM_RESOURCES] = { 1, 2, 2, 1 };

    // Calculate the need matrix
    for (int i = 0; i < NUM_PROCESSES; i++)
        for (int j = 0; j < NUM_RESOURCES; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    // Check if the system is in a safe state and print the result
    if (isSafeState(allocation, max, need, available))
        cout << "System is in a safe state.\n";
    else
        cout << "System is in an unsafe state.\n";

    return 0;
}
