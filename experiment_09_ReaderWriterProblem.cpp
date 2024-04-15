#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore.h> // Include semaphore header for Linux

using namespace std;

class ReadersWriters {
private:
    mutex mutex;           // Mutex for readers count synchronization
    sem_t write_mutex;     // Semaphore for write lock
    int readers_count;     // Count of active readers

public:
    ReadersWriters() : readers_count(0) {
        // Initialize the semaphore
        sem_init(&write_mutex, 0, 1);
    }

    // Method for readers to start reading
    void start_read() {
        mutex.lock();        // Lock mutex to update readers count
        readers_count++;     // Increment readers count
        if (readers_count == 1) {
            sem_wait(&write_mutex); // Acquire write lock if first reader
        }
        mutex.unlock();      // Unlock mutex

        // Reading the shared resource
        cout << "Reader is reading" << endl;

        mutex.lock();        // Lock mutex to update readers count
        readers_count--;     // Decrement readers count
        if (readers_count == 0) {
            sem_post(&write_mutex); // Release write lock if last reader
        }
        mutex.unlock();      // Unlock mutex
    }

    // Method for writers to start writing
    void start_write() {
        sem_wait(&write_mutex); // Acquire write lock

        // Writing to the shared resource
        cout << "Writer is writing" << endl;

        sem_post(&write_mutex); // Release write lock
    }
};

// Function for reader threads
void reader_thread(ReadersWriters& rw, int id) {
    while (true) {
        // Reading
        rw.start_read();
        // Simulating some delay for reading
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

// Function for writer threads
void writer_thread(ReadersWriters& rw, int id) {
    while (true) {
        // Writing
        rw.start_write();
        // Simulating some delay for writing
        this_thread::sleep_for(chrono::milliseconds(2000));
    }
}

int main() {
    ReadersWriters rw;

    // Creating reader threads
    thread readers[5];
    for (int i = 0; i < 5; ++i) {
        readers[i] = thread(reader_thread, ref(rw), i);
    }

    // Creating writer threads
    thread writers[2];
    for (int i = 0; i < 2; ++i) {
        writers[i] = thread(writer_thread, ref(rw), i);
    }

    // Joining threads
    for (int i = 0; i < 5; ++i) {
        readers[i].join();
    }
    for (int i = 0; i < 2; ++i) {
        writers[i].join();
    }

    return 0;
}
