#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

void print_tokens(const AList_t *tokens);

int main(void) {
    char *buffer = file_to_string("../test.json");
    AList_t *tokens = tokenizer(buffer);
    free(buffer); buffer = NULL;

    print_tokens(tokens);

    free_tokens(tokens);
    return 0;
}

void print_tokens(const AList_t *tokens) {
    if (!tokens) {
        printf("No tokens to print\n");
        return;
    }

    for (size_t i = 0; i < tokens->length; i++) {
        const token_t *token = *(token_t **) array_list_get(tokens, i);
        if (token->str) {
            printf("\x1B[32m%s\x1B[0m%s\n", token_type_to_str[token->type], token->str);
        } else {
            printf("\x1B[32m%s\x1B[0m\n", token_type_to_str[token->type]);
        }
    }
}
