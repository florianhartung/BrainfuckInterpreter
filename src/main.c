#include <stdio.h>
#include "include/bfinterpreter.h"

#define MAX_PROGRAM_LENGTH 1000
#define MAX_BRAINFUCK_MEMORY 1000

/**
 * Reads the brainfuck program file given by the first argument.
 * Inputs for the brainfuck program can be given via the second argument (optional).
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("The brainfuck program file must be given as an argument.");
        return 1;
    }

    FILE *program_file;
    if (fopen_s(&program_file, argv[1], "r") != 0) {
        printf("Could not read file %s", argv[0]);
        return 1;
    }


    char program_file_content[MAX_PROGRAM_LENGTH];
    int buffer;
    int pos = 0;
    while ((buffer = fgetc(program_file)) != EOF) {
        program_file_content[pos++] = (char) buffer;
    }

    char *inputs;
    if (argc > 2) {
        inputs = argv[2];
    } else {
        inputs = "";
    }

    return run(program_file_content, inputs);
}
