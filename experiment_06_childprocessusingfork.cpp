#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    pid_t childPid = fork(); // Fork a child process

    if (childPid < 0) {
        cerr << "Error: Fork failed" << endl;
        return 1;
    } else if (childPid == 0) { // Child process
        cout << "Child process: My PID is " << getpid() << endl;
        cout << "Child process: My parent's PID is " << getppid() << endl;

        // Perform child-specific operations here

        return 0; // Exit the child process
    } else { // Parent process
        cout << "Parent process: I have a child with PID " << childPid << endl;
        cout << "Parent process: My PID is " << getpid() << endl;

        // Perform parent-specific operations here

        int status;
        waitpid(childPid, &status, 0); // Wait for the child process to finish
    }

    return 0;
}
