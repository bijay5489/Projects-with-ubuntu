/*********************************************************************
* Author: Bijay Panta
* Created: June 24, 2024
*
* This program implements a simple master-worker threading model to simulate
* a producer-consumer scenario. Master threads produce integers into a shared buffer,
* while worker threads consume these integers.
*links
*https://www.baeldung.com/cs/os-busy-waiting
*https://stackoverflow.com/questions/8156603/is-usleep-in-c-implemented-as-busy-wait
**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 1000

int* buffer; // Pointer for dynamic allocation
int buffer_size;               
int num_to_produce;            
int produced_count = 0; // Counting item produced and placed in the buffer.
int consumed_count = 0;        // Counting item consumed and removed from the buffer.
int next_number_to_produce = 0;// The next number to be produced by the master threads.
int next_number_to_consume = 0;// The next number to be consumed by the worker threads from the buffer.

/*
* Print the number produced and the master thread id.
* input - num: the number produced, thread_id: the id of the master thread
* output - none
*/
void print_produced(int num, int thread_id) {
    printf("Produced: %d by master thread %d\n", num, thread_id);
}

/*
* Print the number consumed and the worker thread id.
* input - num: the number consumed, thread_id: the id of the worker thread
* output - none
*/
void print_consumed(int num, int thread_id) {
    printf("Consumed: %d by worker thread %d\n", num, thread_id);
}

/*
* Input:
*   arg - void pointer to thread specific data (here, it's used for thread ID)
*
* Output:
*   None, function returns NULL after completing its execution.
* 
*   This function inserts numbers into a shared buffer.
*   It implements a busy waiting mechanism to handle full buffer conditions and 
*   stops producing when all numbers are produced.
*/
void* master_thread(void *arg) {
    int thread_id = *(int *)arg;
    while (1) {
        // Busy wait for buffer space. This loop goes until space is available.
        while (produced_count - consumed_count >= buffer_size) {
            usleep(10); // Sleep to reduce CPU usage during the wait. This was not mentioned in our reading however, 
            //There's literally no way of around this unless we continuously checking a condition in a loop, but that will consume a lot of CPU resources.
        }

        // Breaks the loop if all numbers have been produced.
        if (next_number_to_produce >= num_to_produce) break;

        int num = next_number_to_produce; // Initialize 'num' with the current number to be produced. 
        buffer[num % buffer_size] = num; // Assign 'num' to buffer at index. Alternative to this logic would be Busy Waiting with Status Flags. Which would be very tedious.
        next_number_to_produce++; 
        produced_count++;
        
        // Logs the production of the number.
        print_produced(num, thread_id);
    }
    return NULL;
}

/*
* Input:
*   arg - void pointer to thread specific data (here, it's used for thread ID)
*
* Output:
*   None, function returns NULL after all numbers are consumed or the loop is explicitly broken.
* 
* Description:
*   This function removes numbers from a shared buffer.
*   It implements a busy waiting mechanism to handle empty buffer conditions.
*/
void* worker_thread(void *arg) {
    int thread_id = *(int *)arg;
    while (1) {
        // Busy wait for items to consume. This loop goes until there are items.
        while (produced_count <= consumed_count) {
            usleep(10); // Sleep to reduce CPU usage during the wait. 
            if (consumed_count >= num_to_produce) return NULL; // Breaks loop and exits if all produced items have been consumed.
        }

        // Consume the next available number from the buffer.
        int num = buffer[next_number_to_consume % buffer_size];
        next_number_to_consume++;
        consumed_count++;

        // Logs the consumption of the number.
        print_consumed(num, thread_id);

        // Breaks loop and exits if all produced items have been consumed.
        if (consumed_count >= num_to_produce) break;
    }
    return NULL;
}

/*
* Main function to set up and execute threads.
* input - argc: count of command-line arguments,
*         argv: array of command-line arguments
* output - returns 0 In success 
*/
int main(int argc, char *argv[]) {
    //All given to us in the skeleton code.
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <M> <N> <C> <P>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    num_to_produce = atoi(argv[1]);
    buffer_size = atoi(argv[2]);
    int num_workers = atoi(argv[3]);
    int num_masters = atoi(argv[4]);

    if (buffer_size > MAX_BUFFER_SIZE) {
        fprintf(stderr, "Error: Buffer size exceeds maximum allowed size of %d\n", MAX_BUFFER_SIZE);
        exit(EXIT_FAILURE);
    }

    buffer = (int*)malloc(buffer_size * sizeof(int)); // Allocate memory for the buffer
    if (buffer == NULL) {
        fprintf(stderr, "Failed to allocate memory for buffer\n");
        exit(EXIT_FAILURE);
    }

    pthread_t master_threads[num_masters];
    pthread_t worker_threads[num_workers];
    int master_ids[num_masters];
    int worker_ids[num_workers];

    // Create master threads
    for (int i = 0; i < num_masters; i++) {
        master_ids[i] = i; // Assign an ID to each master thread
        pthread_create(&master_threads[i], NULL, master_thread, &master_ids[i]); // Create a master thread that runs master_thread function

    }

    // Create worker threads
    for (int i = 0; i < num_workers; i++) {
        worker_ids[i] = i; 
        pthread_create(&worker_threads[i], NULL, worker_thread, &worker_ids[i]); // Create a worker thread that runs worker_thread function

    }

    // Wait for all master threads to complete
    for (int i = 0; i < num_masters; i++) {
        pthread_join(master_threads[i], NULL); 
    }

    // Wait for all worker threads to complete
    for (int i = 0; i < num_workers; i++) {
        pthread_join(worker_threads[i], NULL); 
    }

    free(buffer); // Free the dynamically allocated buffer memory

    return 0; // Return success
}
