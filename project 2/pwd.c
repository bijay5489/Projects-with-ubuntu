/*********************************************************************
* Author: BIJAY PANTA
* Created: 6/12/2024
*
* This program prints the current working directory.
**********************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_PATH_LENGTH 1024 // Define a constant for the max length of the path.

/*
 * input - None
 * output - Returns 0 on successful execution
 *
 * This function retrieves and prints the current working directory.
 * If an error occurs, it prints an error message to stderr.
 */

int main() {
    char cwd[MAX_PATH_LENGTH]; // Buffer to store the current working directory.
    char error_message[30] = "An error has occurred\n"; 

    if (getcwd(cwd, sizeof(cwd)) != NULL) { // Attempt to get the current working directory.
        printf("%s\n", cwd); // Print the current working directory.
    } else {
        write(STDERR_FILENO, error_message, strlen(error_message)); 
    }

    return 0; 
}
