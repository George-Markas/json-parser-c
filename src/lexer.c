#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char *file_to_string(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Could not open file '%s'\n", filename);
        exit(EXIT_FAILURE);
    }

    fseek(f, 0, SEEK_END);
    const long size = ftell(f);
    rewind(f);

    char *buffer = malloc(size + 1);
    assert(buffer);

    fread(buffer, 1, size, f);
    buffer[size] = '\0';
    fclose(f);

    return buffer;
}
