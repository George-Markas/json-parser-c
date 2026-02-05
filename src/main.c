#include <stdlib.h>
#include "lexer.h"
#include "utf-8.h"

#define TEST_FILE "../tests/text.txt"

int main(void) {
    const char *str = file_to_string(TEST_FILE);
    u8_print_string(str);
    free((void *) str);

    return EXIT_SUCCESS;
}
