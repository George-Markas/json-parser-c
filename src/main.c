#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "utf-8.h"

#define TEST_FILE "../tests/text.txt"

void print_u8_string(const char *str);

int main(void) {
    const char *str = file_to_string(TEST_FILE);
    print_u8_string(str);
    free((void *) str);

    return 0;
}

void print_u8_string(const char *str) {
    u8char_t ch;
    int length;
    const char *temp = str;

    while ((length = u8_next(temp, &ch))) {
        char bytes[5] = {0};
        for (int i = 0; i < length; i++) {
            bytes[i] = (char)((ch >> (8 * (length - 1 - i))) & 0xFF);
        }

        printf("%s", bytes);
        temp += length;
    }
    putchar('\n');
}
