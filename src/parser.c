#include "parser.h"
#include "tokenizer.h"
#include "ansi.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void parse(const char *filename) {
    /* The parser has not been implemented yet */

    AList_t *tokens = tokenize(filename);
    assert(tokens);

    for (size_t i = 0; i < tokens->length; i++) {
        const token_t token = *(token_t *) array_list_get(tokens, i);
        const char *token_str = (token.str) ? token.str : "";
        printf(GREEN(REGULAR)"%s"RESET"%s\n", token_type_to_str[token.type], token_str);
        if (token.str) free(token.str);
    }
    array_list_delete(tokens);
}
