/*********************************************************************
* Author: Bijay Panta
* Created: 6/17/24
*
* The program implements a Round Robin scheduler in C. The scheduler processes a list of tasks, each with a burst time, 
* and simulates their execution with a given time slice. The program prints the completion time for each process.
* Helpfull links
* https://www.javatpoint.com/round-robin-program-in-c
* https://www.geeksforgeeks.org/program-for-round-robin-scheduling-for-the-same-arrival-time/
* 537(1).pdf
**********************************************************************/

#include <stdio.h>

// Define the Process Structure
typedef struct {
    int id;               // Process ID
    int burst_time;       // Total CPU time required by the process
    int remaining_time;   // Remaining CPU time for the process to complete
    int completed;        // Flag indicating if the process is completed (0: not completed, 1: completed)
    int completion_time;  // Time at which the process completes execution
} Process;

/*
* input
* processes: array of Process structures
* n: number of processes
* burst_times: array containing burst times for each process
*
* No outputs void function
*
*initialize the processes with their IDs, burst times, remaining times, and completion status
*/

void initialize_processes(Process processes[], int n, int burst_times[]) {
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1; // Assign a unique ID to each process starting from 1
        processes[i].burst_time = burst_times[i]; // Set the burst time of the process
        processes[i].remaining_time = burst_times[i]; // Initialize remaining time with the burst time
        processes[i].completed = 0; // Mark the process as not completed
    }
}

/*
* input
* processes: array of Process structures
* n: number of processes
* time_slice: time slice for the Round Robin scheduler
*
* No outputs it's void function.
*
* Function to implement the Round Robin scheduling algorithm
*/

void round_robin_scheduler(Process processes[], int n, int time_slice) {
    int time = 0; // Initialize current time in the simulation
    int completed_processes = 0; // Initialize the count of completed processes

    // Continue looping until all processes are completed, check the 537.pdf file for a Visual example
    while (completed_processes < n) {
        for (int i = 0; i < n; i++) {
            // Check if the process is not completed.If processes[i].completed is 0, the process has not yet completed and needs to be scheduled for execution.
            if (processes[i].completed == 0) {
                // If the remaining time is greater than the time slice, execute the process for the time slice. Is checking remaining time being greater or not.
                if (processes[i].remaining_time > time_slice) {
                    processes[i].remaining_time -= time_slice; // Deduct the time slice from the remaining time. Helpful reference https://www.geeksforgeeks.org/program-for-round-robin-scheduling-for-the-same-arrival-time/
                    time += time_slice; // Increment the current time by the time slice.
                } else {
                    // the else completes the process where the remaining execution time of the process is less or equal to the time slice.
                    time += processes[i].remaining_time; // Increment the current time by the remaining time.
                    processes[i].remaining_time = 0; // Set the remaining time to zero
                    processes[i].completed = 1; // Mark the process as completed
                    processes[i].completion_time = time; // Record the completion time of the process
                    completed_processes++; // Increment the count of completed processes
                }
            }
        }
    }
}

/*
* Function: main
* --------------
* Main function to execute the Round Robin scheduler.
* 
* Input
* user input for number of processes, burst times, and time slice,
*
* Outputs the completion times for each process.
*/

int main() {
    int n;           // Number of processes
    int time_slice;  // Time slice for the scheduler

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst_times[n];  // Array to store burst times for each process

    // Input burst times for each process
    printf("Enter the burst times for each process: ");
    for (int i = 0; i < n; i++) { //The for loop iterates over each process (from 0 to n-1),reading and storing it in the burst_times array.
        scanf("%d", &burst_times[i]);
    }

    // Input time slice, reads and stores it.
    printf("Enter the time slice: ");
    scanf("%d", &time_slice);

    // Initialize processes
    Process processes[n]; //Declares an array processes of type Process with size n.
    initialize_processes(processes, n, burst_times); //Calls the function to initialize the processes array with the IDs and burst times of each process.

    round_robin_scheduler(processes, n, time_slice); // Run the Round Robin scheduler

    // Print completion times
    printf("Completion times:\n");
    for (int i = 0; i < n; i++) { //need this loop to print in order instead of whatever processor finished first.
        printf("Process %d completed at time %d\n", processes[i].id, processes[i].completion_time);
    }


    return 0;
}

