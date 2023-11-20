/**
 * Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author Salman Burhan
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

bool should_run = true;
Buffer buffer;
pthread_mutex_t mutex;
sem_t sema_empty;
sem_t sema_full;

// Producer thread function
// Add your implementation of the producer thread here
void *producer(void *param) {
    // Each producer insert its own ID into the buffer
    // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.
    buffer_item item = *((int *)param);

    while (should_run) {
        /* sleep for a random period of time */
        usleep(rand() % 1000000);

        /* wait for signal */
        sem_wait(&sema_empty);
        /* lock to prevent parallel threads */
        pthread_mutex_lock(&mutex);

        if (buffer.insert_item(item)) {
            std::cout << "Producer " << item << ": Inserted item " << item
                      << std::endl;
            buffer.print_buffer();
        } else {
            std::cout << "Producer error condition" << std::endl;
        }
        /* unlock */
        pthread_mutex_unlock(&mutex);
        /* signal */
        sem_post(&sema_full);
    }
}

// Consumer thread function
// Add your implementation of the consumer thread here
void *consumer(void *param) {
    buffer_item item;

    while (should_run) {
        /* sleep for a random period of time */
        usleep(rand() % 1000000);

        /* wait for signal */
        sem_wait(&sema_full);
        /* lock to prevent parallel threads */
        pthread_mutex_lock(&mutex);

        if (buffer.remove_item(&item)) {
            std::cout << "Consumer "
                      << " Removed item " << item << std::endl;
            buffer.print_buffer();
        } else {
            std::cout << "Consumer error condition" << std::endl;
        }

        /* unlock */
        pthread_mutex_unlock(&mutex);
        /* signal */
        sem_post(&sema_empty);
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
    pthread_t thread;
    int producer_ids[num_producer];

    /*
     * MacOS (Darwin) doesn’t support unnamed semaphores, and therefore:
     *  sem_init()
     *  sem_destroy()
     * MacOS (Darwin) only supports named semaphores, and therefore:
     *  sem_open()
     *  sem_close()
     */
    sem_init(&sema_empty, 0, buffer.get_size());
    sem_init(&sema_full, 0, 0);

    /* 3. Create producer thread(s).
     * You should pass an unique int ID to each producer thread, starting
     * from 1 to number of threads */

    /* 3. Create producer thread(s). */
    for (int i = 1; i <= num_producer; i++) {
        producer_ids[i - 1] = i;
        // Arguments: [thread] [attributes] [threadFunction] [identifier]
        pthread_create(&thread, NULL, &producer, &producer_ids[i - 1]);
    }

    /* 3. Create consumer thread(s). */
    for (int i = 1; i <= num_consumer; i++) {
        // Arguments: [thread] [attributes] [threadFunction] [identifier]
        pthread_create(&thread, NULL, &consumer, NULL);
    }

    /* 5. Main thread sleep */
    usleep(sleep_time * 1000000);

    /* 6. Exit */
    should_run = false;
    pthread_mutex_destroy(&mutex);
    sem_destroy(&sema_empty);
    sem_destroy(&sema_full);
    exit(0);

    return 0;
}
