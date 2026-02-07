#include <printf.h>
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "utf-8.h"

#define TEST_FILE "../tests/text.txt"

int main(void) {
    register_uchar8_t_printf();

    const char *u1 = file_to_string(TEST_FILE);
    printf("%s\n", u1);
    free((void *) u1);

    const char *u2 = "💘";
    u8char_t ch;
    u8_next(u2, &ch);

    printf("Through custom specifier: %U\n", ch);

    return EXIT_SUCCESS;
}
