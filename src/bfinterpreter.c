#include <stdio.h>
#include <string.h>

#define MAX_BRAINFUCK_MEMORY 1000

int seek_end_of_loop(const char *program, const int program_pointer) {
    int nested_loop_count = 0;
    for (int i = program_pointer; i < strlen(program); ++i) {
        if (program[i] == '[') {
            nested_loop_count++;
        } else if (program[i] == ']') {
            nested_loop_count--;
            if (nested_loop_count == 0) {
                return i;
            }
        }
    }
    return -1;
}
int seek_start_of_loop(const char *program, const int program_pointer) {
    int nested_loop_count = 0;
    for (int i = program_pointer; i > 0; --i) {
        if(program[i] == ']') {
            nested_loop_count++;
        } else if (program[i] == '[') {
            nested_loop_count--;
            if(nested_loop_count == 0) {
                return i;
            }
        }
    }
    return -1;
}

int run(char *program, char *inputs) {
    unsigned int input_length = strlen(inputs);
    int input_pointer = 0;

    int memory[MAX_BRAINFUCK_MEMORY] = {0};
    int memory_pointer = MAX_BRAINFUCK_MEMORY / 2;

    int program_pointer = 0;

    while (program_pointer < strlen(program)) {
        char c = program[program_pointer];
        switch (c) {
            case '+':
                memory[memory_pointer]++;
                break;
            case '-':
                if(memory[memory_pointer] > 0) {
                    memory[memory_pointer]--;
                }
                break;
            case '>':
                memory_pointer++;
                break;
            case '<':
                memory_pointer--;
                break;
            case '.':
                printf("%c", memory[memory_pointer]);
                break;
            case ',':
                if (input_pointer >= input_length) {
                    printf("\nError: No more inputs present");
                    return 1;
                }
                memory[memory_pointer] = (int) inputs[input_pointer++];
                break;
            case '[':
                if(memory[memory_pointer] == 0) {
                    program_pointer = seek_end_of_loop(program, program_pointer);
                    if(program_pointer == -1) {
                        printf("\nError: Could not find end of loop");
                        return 1;
                    }
                }
                break;
            case ']':
                if(memory[memory_pointer] > 0) {
                    program_pointer = seek_start_of_loop(program, program_pointer);
                    if(program_pointer == -1) {
                        printf("\nError: Could not find end of loop");
                        return 1;
                    }
                }
                break;
            default:
                break;
        }
        program_pointer++;
    }

    return 0;
}