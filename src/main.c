#include <stdlib.h>
#include "utf-8.h"
#include "tokenizer.h"
#include "parser.h"

int main(void) {
    register_uchar8_t_printf();

    const char *str = file_to_string("../tests/json_types.txt");
    parse(str);

    free((void *) str);

    return EXIT_SUCCESS;
}
