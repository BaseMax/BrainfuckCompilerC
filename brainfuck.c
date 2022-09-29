/*
 * Name: Brainfuck Compiler C
 * Author: Max Base
 * Date: 2022/09/29
 * Repository: https://github.com/basemax/BrainfuckCompilerC
 */

#include <stdio.h>
#include <stdlib.h>

char* read_from_cli() {
    char* program = malloc(10000 * sizeof(char));

    int i = 0;
    while((program[i++] = getchar()) != 'x');

    program[i-1] = '\0';

    return program;
}

char* read_from_file(char* filepath) {
	FILE* file = fopen(filepath, "rb");
	if (file == NULL) {
		printf("Error: Could not open file \"%s\".", filepath);
		exit(74);
	}

	fseek(file, 0L, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	char* program = (char*)malloc(fileSize + 1);
	if (program == NULL) {
		printf("Error: Not enough memory to read \"%s\".", filepath);
		exit(74);
	}

	size_t bytesRead = fread(program, sizeof(char), fileSize, file);
	if (bytesRead < fileSize) {
		printf("Error: Could not read the \"%s\".", filepath);
		exit(74);
	}

	program[bytesRead] = '\0';

	fclose(file);
	return program;
}

char* run(char* program) {
    char* c = malloc(10000 * sizeof(char));
}

int main(int argc, char** argv) {
    char* c = NULL;
    char* program = NULL;

    if (argc > 2) {
        printf("Error: ./%s [file.bf]\n", argv[0]);
        return 1;
    } else if (argc == 1) {
        program = read_from_cli();
    } else {
        program = read_from_file(argv[1]);
    }

    if (program != NULL) {
        printf("%s\n===========\n", program);
        c = run(program);
        free(program);

        printf("%s", c);

        FILE* file = fopen("out.c", "w");
        fprintf(file, "%s", c);
        fclose(file);

        free(c);
    }

    return 0;
}
