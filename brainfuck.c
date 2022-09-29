/*
 * Name: Brainfuck Compiler C
 * Author: Max Base
 * Date: 2022/09/29
 * Repository: https://github.com/basemax/BrainfuckCompilerC
 */

#include <stdio.h>
#include <stdlib.h>

char* read_from_cli() {
    char* program = malloc(10000*sizeof(char));

    int i = 0;
    while((program[i++] = getchar()) != 'x');

    program[i-1] = '\0';

    return program;
}

char* read_from_file(char* file_path) {
    FILE* file = fopen(file_path, "r");
    if(file == NULL) {
        printf("File not found: %s\n", file_path);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    if (size <= 0) return "";

    char* program = malloc(size*sizeof(char));
    fread(program, sizeof(char), size, file);
    fclose(file);

    return program;
}

char* run(char* program) {

}

int main(int argc, char** argv) {
    char* c = NULL;

    if (argc > 2) {
        printf("Error: ./%s [file.bf]\n", argv[0]);
        return 1;
    } else if (argc == 1) {
        char* program = read_from_cli();
        c = run(program);
        free(program);
    } else {
        char* program = read_from_file(argv[1]);
        c = run(program);
        free(program);
    }

    if (c != NULL) {
        printf("%s", c);

        FILE* file = fopen("out.c", "w");
        fprintf(file, "%s", c);
        fclose(file);

        free(c);
    }

    return 0;
}
