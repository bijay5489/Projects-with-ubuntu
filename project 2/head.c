/*********************************************************************
* Author: BIJAY PANTA
* Created: 6/12/2024
*
* This program reads and prints the first 10 lines of a specified file.
**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define LINES_TO_PRINT 10 // the number of lines to print.
#define ERROR_MESSAGE "An error has occurred\n" // Define a constant for the error message.

/*
* 
* input - 
*   argc: Number of command-line arguments.
*   argv: Array of command-line arguments.
* output - 
*   Returns 0 on success, 1 on error.
*
* Entry point of the program. Reads a file and prints the first 10 lines.
*/

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }
    
    // Attempt to open the file for reading
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        write(STDERR_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE)); 
        return 1;
    }
    
    char line[256]; // Buffer to store each line read from the file
    int count = 0; // Counter for the number of lines printed
    
    // Read and print lines from the file up to LINES_TO_PRINT
    while (fgets(line, sizeof(line), file) != NULL && count < LINES_TO_PRINT) {
        printf("%s", line); 
        count++; 
    }
    
    fclose(file); 
    return 0;
}
