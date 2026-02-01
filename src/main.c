#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "parser.h"

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
        if (tok->type == TOK_STRING && tok->string != NULL) {
            printf("\x1B[32m%s\x1B[0m %s\n", tok_type_to_str[tok->type], tok->string);
        } else if (tok->type == TOK_NUMBER) {
            printf("\x1B[32m%s\x1B[0m %g\n", tok_type_to_str[tok->type], tok->number);
        } else if (tok->type == TOK_TRUE || tok->type == TOK_FALSE) {
            const char *val = tok->boolean ? "true" : "false";
            printf("\x1B[32m%s\x1B[0m %s\n", tok_type_to_str[tok->type], val);
        } else if (tok->type == TOK_NULL) {
            printf("\x1B[32m%s\x1B[0m null\n", tok_type_to_str[tok->type]);
        } else {
            printf("\x1B[32m%s\x1B[0m %c\n", tok_type_to_str[tok->type], tok->character);
        }
    }
}

void free_tokens(const AList_t *tokens) {
    for (size_t i = 0; i < tokens->length; i++) {
        token_t *tok = *(token_t **) array_list_get(tokens, i);
        if (tok->type == TOK_STRING && tok->string != NULL) {
            free(tok->string); tok->string = NULL;
        }

        free(tok); tok = NULL;
    }
}