/*********************************************************************
* Author: Bijay Panta
* Created: 6/3/2024
*
* The program reads a text file, reverses the order of its lines, and then either displays the reversed content on the screen or writes it to another specified output file.
**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024 // Defines the maximum length for a line of text read from the file. 

    // Global pointers and variables initialization:
    char **lines = NULL; // Pointer to an array of char pointers. Each pointer in the array will point to a string for a line in the file.
    char buffer[MAX_LINE_LENGTH]; // Buffer array to temporarily store each line read from the file before it is processed or stored.
    int capacity = 10; // Initial capacity of the lines array.
    int line_count = 0; // Counter for the number of lines actually read and stored.


/*
* This function iterates over an array of string pointers, freeing each string, then finally frees the array itself. 
* inputs:
 *   lines: A pointer to an array of char pointers (strings). Each string is
 *          dynamically allocated and needs to be freed.
 *   count: The number of strings in the array. 
 *
 * outputs:
 *   There are no  outputs from this function, it returns void. 
 */

void free_memory(char **lines, int count) {
    for (int i = 0; i < count; i++) {
        free(lines[i]);  
    }
    free(lines); 
}

/*
 * This function iterates over an array of strings from the last element to the first, printing each string to the provided file stream followed by a newline. 
 *
 * Inputs:
 *   lines: A pointer to an array of char pointers.
 *   count: The number of elements in the 'lines' array.
 *   fp:    A file pointer to a FILE stream where the lines will be output.
 *
 * Outputs:
 *   There are no outputs from this function, it returns void. 
 */

void reverse_lines_and_output(char **lines, int count, FILE *fp) {
    for (int i = count - 1; i >= 0; i--) {
        fprintf(fp, "%s\n", lines[i]);
    }
}

/*
 * Reads a text file, reverses its lines,and outputs them either to a specified file or stdout.
 *
 * Inputs:
 *   argument_count - Integer count of command-line arguments.
 *   argument_values - Array of character pointers listing all command-line arguments.
 *
 * Outputs:
 *   Returns an integer status code. 0 indicates successful execution, and 1 indicates an error with appropriate error messages output to stderr.
*/

int main(int argument_count, char *argument_values[]) {
    if (argument_count < 2 || argument_count > 3) {
        fprintf(stderr, "usage: rcat input <output>\n");
        return 1;
    }
    // Assign filenames
    char *input_filename = argument_values[1];
    char *output_filename = argument_count == 3 ? argument_values[2] : NULL;

    // Check if input and output filenames are the same
    if (output_filename && strcmp(input_filename, output_filename) == 0) {
        fprintf(stderr, "Input and output file must differ\n");
        return 1;
    }

    // Attempt to open the input file
    FILE *input_file = fopen(input_filename, "r");
    if (!input_file) {
        fprintf(stderr, "error: cannot open file '%s'\n", input_filename);
        return 1;
    }

    // Initialize memory allocation for storing lines. The array will store pointers to each line read from the file.
    lines = malloc(capacity * sizeof(char *));
    if (!lines) {
        fprintf(stderr, "malloc() failed\n");
        fclose(input_file);
        return 1;
    }

    //Reads each line from the INPUT FILES.
    while (fgets(buffer, MAX_LINE_LENGTH, input_file)) {
        //Before storing the new line, we checks if the current array lines has enough space. If not, it doubles the capacity using realloc.
        if (line_count == capacity) {
            capacity *= 2;
            char **new_lines = realloc(lines, capacity * sizeof(char *));
            if (!new_lines) {
                fprintf(stderr, "realloc() failed\n");
                fclose(input_file);
                free_memory(lines, line_count);
                return 1;
            }
            lines = new_lines;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        lines[line_count++] = strdup(buffer);
    }
    fclose(input_file);
    
    //Open the output file or it uses the standard output.
    FILE *output_file = output_filename ? fopen(output_filename, "w") : stdout;
    if (output_filename && !output_file) {
        fprintf(stderr, "error: cannot open file '%s'\n", output_filename);
        free_memory(lines, line_count);
        return 1;
    }

    reverse_lines_and_output(lines, line_count, output_file); // Reverse and output lines

    if (output_file != stdout) {
        fclose(output_file);
    }

    free_memory(lines, line_count); // Free dynamic memory

    return 0;
}

