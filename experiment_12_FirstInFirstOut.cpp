#include <iostream>
#include <unordered_set>
#include <queue>

using namespace std;

// Function to find page faults using FIFO
int pageFaults(int pages[], int n, int capacity)
{
    unordered_set<int> pageSet; // To represent set of current pages
    queue<int> pageQueue;       // To store the pages in FIFO manner
    int pageFaults = 0;         // Initialize page faults count

    for (int i = 0; i < n; i++)
    {
        // Check if the set can hold more pages
        if (pageSet.size() < capacity)
        {
            // Insert page into set if not present already (page fault)
            if (pageSet.find(pages[i]) == pageSet.end())
            {
                pageSet.insert(pages[i]);    // Insert current page into set
                pageFaults++;                // Increment page fault count
                pageQueue.push(pages[i]);    // Push current page into the queue
            }
        }
        else
        {
            // Check if current page is not already present in the set
            if (pageSet.find(pages[i]) == pageSet.end())
            {
                int val = pageQueue.front(); // Store the first page in the queue
                pageQueue.pop();             // Pop the first page from the queue
                pageSet.erase(val);          // Remove the first page from the set
                pageSet.insert(pages[i]);    // Insert the current page into the set
                pageQueue.push(pages[i]);    // Push the current page into the queue
                pageFaults++;                // Increment page fault count
            }
        }
    }

    return pageFaults;
}

// Driver code
int main()
{
    int pages[] = {1, 3, 0, 3, 5, 6, 1, 0, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;
    cout << "Page Faults: " << pageFaults(pages, n, capacity) << endl;
    return 0;
}
