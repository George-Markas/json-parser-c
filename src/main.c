#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "parser.h"

int main(void) {
    const char *str = file_to_string("../tests/json_types.txt");

    dummy_parse(str);

    free((void *) str);

    return EXIT_SUCCESS;
}
