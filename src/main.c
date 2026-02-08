#include <stdlib.h>
#include "utf-8.h"
#include "tokenizer.h"
#include "parser.h"

#ifndef NDEBUG
#define TEST_TEXT "../tests/text.txt"
#define TEST_JSON "../tests/simple_json.txt"
#define TEST_U8_JSON "../tests/utf-8_json.txt"
#endif

int main(void) {
    register_uchar8_t_printf();

    const char *str = file_to_string(TEST_U8_JSON);
    parse(str);

    free((void *) str);

    return EXIT_SUCCESS;
}
