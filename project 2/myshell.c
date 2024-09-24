/*********************************************************************
* Author: BIJAY PANTA
* Created: 6/12/2024
*
* This program implements a basic shell that can execute commands.
* It supports background execution of commands and handles basic
* built-in commands such as "exit". 
*
* 
*
*
**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //in the reading
#include <sys/wait.h> //in the reading

#define MAX_LINE 1024 // Define a constant for the max length of input line.
#define MAX_ARGS 64  // Define a constant for the max number of arguments.
    char line[MAX_LINE]; // Buffer array to store the input line.
    char *args[MAX_ARGS]; // Array of pointers to store the arguments of the command.
    int background; // Flag to indicate if the command should run in the background.

/*
 * Forks a child process to execute a command. The command is specified by the args array.
 * If the background parameter is set to 1, the command is executed in the background.
 * If background is 0, the shell waits for the command to complete before accepting new input.
 *
 * Inputs:
 *   args[]: The command and its arguments to be executed.
 *   background: A flag indicating whether to run the command in the background.
 *
 * Outputs:
 *  it returns void.
 */

void execute_command(char *args[], int background);

/*
* main - Entry point of the shell program
* input - None
* output - Returns 0 on successful execution
*
* This function reads commands from the user, parses them,
* and executes them.
*/

int main() {    
    while (1) {
        printf("myshell> "); // Prompt for the shell
        if (fgets(line, MAX_LINE, stdin) == NULL) { // Read a line of input
            break;
        }

        // Remove trailing newline character
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }

        // Parse the input line into arguments
        char *token = strtok(line, " ");
        int i = 0;
        background = 0;
        
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Check if the command should be run in the background
        if (i > 0 && strcmp(args[i - 1], "&") == 0) {
            background = 1;
            args[i - 1] = NULL;
        }

        // Handle built-in commands
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        // Execute the command
        execute_command(args, background);
    }

    return 0;
}

/*
 * Forks a child process to execute a command. If the command is to be run in the background,
 * the parent process does not wait for the child to complete. Otherwise, it waits for the child
 * process to finish execution.
 *
 * Inputs:
 *   args[]: The command and its arguments to be executed.
 *   background: A flag indicating whether to run the command in the background.
 *
 * Outputs:
 *   It returns void.
 */
void execute_command(char *args[], int background) {
    pid_t pid = fork();
    char error_message[30] = "An error has occurred\n";
    
    if (pid < 0) { // Error occurred during fork
        write(STDERR_FILENO, error_message, strlen(error_message)); // Print error message to stderr
        exit(1);
    } else if (pid == 0) { // Child process
        execvp(args[0], args); // Replace child process with the command
        // If execvp returns, an error occurred
        write(STDERR_FILENO, error_message, strlen(error_message)); // Print error message to stderr
        exit(1);
    } else { // Parent process
        if (!background) { // If the command is not to be run in the background
            waitpid(pid, NULL, 0); // Wait for the child process to complete
        }
    }
}
