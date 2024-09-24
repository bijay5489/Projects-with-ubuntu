/*********************************************************************
* Author: BIJAY PANTA
* Created: 6/12/2024
*
* This program prints all command-line arguments passed to it.
* Each argument is printed followed by a space.
**********************************************************************/

#include <stdio.h>

/*
* input - 
*   argc: Number of command-line arguments.
*   argv: Array of command-line arguments.
* output - 
*   Returns 0 on successful execution.
*
* Entry point of the program. Prints command-line arguments.
*/

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        printf("%s ", argv[i]); 
    }
    printf("\n"); 

    return 0; 
}
