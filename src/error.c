#include "error.h"
#include "ansi.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

static uint8_t int_length(const unsigned int num) {
    if (num >= 1000000000) return 10;
    if (num >= 100000000)  return 9;
    if (num >= 10000000)   return 8;
    if (num >= 1000000)    return 7;
    if (num >= 100000)     return 6;
    if (num >= 10000)      return 5;
    if (num >= 1000)       return 4;
    if (num >= 100)        return 3;
    if (num >= 10)         return 2;
    return 1;
}

static int string_to_int(int num, char *buffer, const int size) {
    if (!buffer) return -1;

    bool negative = false;
    int length = int_length(num);

    if (num < 0) {
        length++;
        negative = true;
    }

    if (length + 1 > size) {
        buffer[0] = '\0';
        return -1;
    }

    buffer[length] = '\0';

    int i = length - negative;
    while (i) {
        i--;
        buffer[i] = (char) (num % 10 + '0');
        num = num / 10;
    }

    return length + 1;
}

void error(const char *file, const int line,  const char *error_message, ...) {
    va_list args;

    va_start(args, error_message);
    const int size = vsnprintf(NULL, 0, error_message, args);
    va_end(args);
    if (!size) {
        fprintf(stderr, "vsnprintf error\n");
        return;
    }

    char *formatted_message = malloc(size + 1);
    if (!formatted_message) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    va_start(args, error_message);
    vsnprintf(formatted_message, size + 1, error_message, args);
    va_end(args);

    char prefix[MAX_LENGTH] = RED(BOLD)"error "RESET;

    if (file) {
        strlcat(prefix, "("YELLOW(BOLD), MAX_LENGTH);
        strlcat(prefix, file, MAX_LENGTH);

        if (line) {
            strlcat(prefix, ":", MAX_LENGTH);
            const int length = (int) strnlen(prefix, MAX_LENGTH);
            char *temp = prefix + length;
            string_to_int(line, temp, MAX_LENGTH - length);
        }

        strlcat(prefix, RESET")", MAX_LENGTH);
    }

    strlcat(prefix, ":", MAX_LENGTH);
    fprintf(stderr, "%s %s\n", prefix, formatted_message);

    free(formatted_message);
}

void not_implemented(const char *feature, const bool terminate) {
    printf(YELLOW(UNDERLINE)"%s"YELLOW(REGULAR)" has not been implemented\n", feature);
    if (terminate) exit(EXIT_FAILURE);
}