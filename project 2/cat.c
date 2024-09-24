/*********************************************************************
* Author: BIJAY PANTA
* Created: 6/12/2024
*
* This program reads and prints the contents of a specified file to the standard output.
**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

#define ERROR_MESSAGE "An error has occurred\n" // Define a constant for the error message
    char ch; // Variable to store each character read from the file

/*
* input - 
*   argc: Number of command-line arguments.
*   argv: Array of command-line arguments.
* output - 
*   Returns 0 on successful execution, 1 on error.
*
* Reads and prints the contents of a file.
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
    
    // Read and print each character from the file until EOF
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch); 
    }
    
    fclose(file);
    return 0; 
}
