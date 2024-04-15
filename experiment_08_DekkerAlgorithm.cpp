#include <iostream>
using namespace std;

int main() {
    int incomingStream[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int pageFaults = 0;
    int frames = 4;
    int memoryIndex, pageIndex, slotIndex, totalPages;
    totalPages = sizeof(incomingStream) / sizeof(incomingStream[0]);

    // Print headers for output display
    cout << "Incoming \t Frame 1 \t Frame 2 \t Frame 3 \t Frame 4\n";

    int framesMemory[frames]; // Array to simulate frames memory
    for (memoryIndex = 0; memoryIndex < frames; memoryIndex++) {
        framesMemory[memoryIndex] = -1; // Initialize frames with -1 (empty)
    }

    for (pageIndex = 0; pageIndex < totalPages; pageIndex++) {
        slotIndex = 0;
        for (memoryIndex = 0; memoryIndex < frames; memoryIndex++) {
            if (incomingStream[pageIndex] == framesMemory[memoryIndex]) {
                slotIndex++;
                pageFaults--; // Page found in memory, decrement page fault count
            }
        }
        pageFaults++; // Increment page fault count

        if ((pageFaults <= frames) && (slotIndex == 0)) {
            framesMemory[pageIndex] = incomingStream[pageIndex];
        } else if (slotIndex == 0) {
            framesMemory[(pageFaults - 1) % frames] = incomingStream[pageIndex];
        }

        cout << "\n";
        cout << incomingStream[pageIndex] << "\t\t\t";
        for (memoryIndex = 0; memoryIndex < frames; memoryIndex++) {
            if (framesMemory[memoryIndex] != -1) {
                cout << framesMemory[memoryIndex] << "\t\t\t";
            } else {
                cout << "- \t\t\t";
            }
        }
    }

    // Print total page faults and hits
    cout << "\n\nTotal Page Faults:\t" << pageFaults;
    cout << "\nTotal Hits :\t" << totalPages - pageFaults;

    return 0;
}
