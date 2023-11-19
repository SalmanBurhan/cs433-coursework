/**
 * Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author ??? (TODO: your name)
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are
// done.
//  Remember to add sufficient and clear comments to your code
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#include <iostream>

#include "buffer.h"

// global buffer object
Buffer buffer;
sem_t *empty_sempahore;
sem_t *full_sempahore;
pthread_mutex_t lock;

// Producer thread function
// Add your implementation of the producer thread here
void *producer(void *param) {
    // Each producer insert its own ID into the buffer
    // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.
    buffer_item item = *((int *)param);

    while (true) {
        /* sleep for a random period of time */
        usleep(rand() % 1000000);

        // Add synchronization code here
        // Lock
        sem_wait(empty_sempahore);
        pthread_mutex_lock(&lock);

        if (buffer.insert_item(item)) {
            std::cout << "Producer " << item << ": Inserted item " << item
                      << std::endl;
            buffer.print_buffer();
        } else {
            std::cout << "Producer error condition"
                      << std::endl;  // shouldn't come here
        }

        // Add synchronization code here
        // Unlock
        pthread_mutex_unlock(&lock);
        sem_post(full_sempahore);
    }
}

// Consumer thread function
// Add your implementation of the consumer thread here
void *consumer(void *param) {
    buffer_item item;

    while (true) {
        /* sleep for a random period of time */
        usleep(rand() % 1000000);

        // Add synchronization code here
        // Lock
        sem_wait(full_sempahore);
        pthread_mutex_lock(&lock);

        if (buffer.remove_item(&item)) {
            std::cout << "Consumer " << item << ": Removed item " << item
                      << std::endl;
            buffer.print_buffer();
        } else {
            std::cout << "Consumer error condition"
                      << std::endl;  // shouldn't come here
        }

        // Add synchronization code here
        // Unlock
        pthread_mutex_unlock(&lock);
        sem_post(empty_sempahore);
    }
}

/**
 * @brief Handles error-checking conversion of an argument to an integer.
 * @param arg the passed CLI argument
 * @return the integer representation of the argument.
 */
int capture(char *arg) {
    try {
        int captured = std::stoi(arg);
        if (captured < 0) {
            std::cout << "Negative Int Argument Passed: " << captured
                      << std::endl;
        } else {
            return captured;
        }
    } catch (const std::invalid_argument) {
        std::cout << "Non Int Argument Passed: " << arg << std::endl;
    } catch (...) {
        std::cout << "Argument Parse Error: " << arg << std::endl;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    /* 1. Get command line arguments argv[1],argv[2],argv[3] */
    if (argc < 4) {
        std::cout
            << "Usage: " << argv[0]
            << " <int: sleep_time> <int: num_producer> <int: num_consumer>"
            << std::endl;
        return 1;
    }

    const int sleep_time = capture(argv[1]);
    const int num_producer = capture(argv[2]);
    const int num_consumer = capture(argv[2]);

    if (sleep_time == -1 || num_producer == -1 | num_consumer == -1) {
        return 1;
    }

    /* 2. Initialize buffer and synchronization primitives */
    pthread_t producer_thread;
    pthread_t consumer_thread;
    lock = PTHREAD_MUTEX_INITIALIZER;  // Convenience Initializer
    // Semaphore Initalizer Arguments: [Name] [isProcessShared], [Value]
    empty_sempahore = sem_open("/empty_semaphore", 0, buffer.get_size());
    full_sempahore = sem_open("/full_semaphore", 0, 0);

    /*
     * MacOS (Darwin) doesn’t support unnamed semaphores, and therefore:
        * sem_init()
        * sem_destroy()
     * MacOS (Darwin) only supports named semaphores, and therefore:
        * sem_open()
        * sem_close()
    /*
    /* ---------------------------------------------------
        sem_init(&empty_sempahore, 0, buffer.get_size());
        sem_init(&full_sempahore, 0, 0);
       --------------------------------------------------- */

    /* 3. Create producer thread(s).
     * You should pass an unique int ID to each producer thread, starting
     * from 1 to number of threads */
    int uid[num_producer];  // Unique IDs of the producers
    for (int i = 0; i < num_producer; i++) {
        uid[i] = i + 1;
        // Initializer Arguments:
        // [thread] [attributes] [threadFunction] [identifier]
        pthread_create(&producer_thread, nullptr, producer, &uid[i]);
    }

    /* 4. Create consumer thread(s) */
    for (int i = 0; i < num_consumer; i++) {
        // Initializer Arguments:
        // [thread] [attributes] [threadFunction] [identifier]
        pthread_create(&consumer_thread, nullptr, consumer, nullptr);
    }

    /* 5. Main thread sleep */
    sleep(sleep_time);

    /* 6. Exit */
    // Semaphore Cleanup
    sem_close(empty_sempahore);
    sem_unlink("/empty_semaphore");
    sem_close(full_sempahore);
    sem_unlink("/full_sempahore");
    // Mutex Destruction
    pthread_mutex_destroy(&lock);
    /* -------------------------------
        sem_destroy(&empty_sempahore);
        sem_destroy(&full_sempahore);
       ------------------------------- */
}
