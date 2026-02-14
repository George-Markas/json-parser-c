#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ansi.h"
#include "tokenizer.h"
#include "parser.h"

void print_tokens(AList_t *tokens);

int main(void) {
    const char *str = file_to_string("../tests/json_types.txt");

    AList_t *tokens = tokenize(str);
    assert(tokens);

    print_tokens(tokens);

    free((void *) str);

    return EXIT_SUCCESS;
}

void print_tokens(AList_t *tokens) {
    if (!tokens) return;
    for (size_t i = 0; i < tokens->length; i++) {
        const token_t token = get_token(tokens, i);
        const char *token_str = (token.str) ? token.str : "";
        printf(GREEN(REGULAR)"%s    "RESET"%s\n", token_type_map[token.type], token_str);
        if (token.str) free(token.str);
    }
    array_list_delete(tokens);
}