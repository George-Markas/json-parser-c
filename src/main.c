#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

void print_tokens(const AList_t *tokens);

void free_tokens(const AList_t *tokens);

int main(void) {
    char *buf = file_to_string("../test.json");
    AList_t *tokens = tokenizer(buf);
    free(buf); buf = NULL;

    print_tokens(tokens);

    free_tokens(tokens);
    array_list_delete(tokens);
    return 0;
}

void print_tokens(const AList_t *tokens) {
    for (size_t i = 0; i < tokens->length; i++) {
        const token_t *tok = *(token_t **) array_list_get(tokens, i);
        if (tok->str) {
            printf("\x1B[32m%s\x1B[0m %s\n", tok_type_to_str[tok->type], tok->str);
        } else {
            printf("\x1B[32m%s\x1B[0m\n", tok_type_to_str[tok->type]);
        }
    }
}

void free_tokens(const AList_t *tokens) {
    for (size_t i = 0; i < tokens->length; i++) {
        token_t *tok = *(token_t **) array_list_get(tokens, i);
        if (tok->str) {
            free(tok->str); tok->str = NULL;
        }

        free(tok); tok = NULL;
    }
}