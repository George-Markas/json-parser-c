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
       const char *tok_type_to_str[] = {
            "\x1B[32mBRACE_OPEN:   \x1B[0m",
            "\x1B[32mBRACE_CLOSE:  \x1B[0m",
            "\x1B[32mBRACKET_OPEN: \x1B[0m",
            "\x1B[32mBRACKET_CLOSE:\x1B[0m",
            "\x1B[32mJSON_COLON:   \x1B[0m",
            "\x1B[32mJSON_COMMA:   \x1B[0m",
            "\x1B[32mJSON_STRING:  \x1B[0m",
            "\x1B[32mJSON_NUMBER:  \x1B[0m",
            "\x1B[32mJSON_BOOLEAN: \x1B[0m",
            "\x1B[32mJSON_NULL:    \x1B[0m"
        };

        const token_t *tok = *(token_t **) array_list_get(tokens, i);
        if (tok->type == JSON_STRING && tok->string != NULL) {
            printf("%s %s\n", tok_type_to_str[tok->type], tok->string);
        } else if (tok->type == JSON_NUMBER) {
            printf("%s %g\n", tok_type_to_str[tok->type], tok->number);
        } else if (tok->type == JSON_BOOLEAN) {
            const char *val = tok->boolean ? "true" : "false";
            printf("%s %s\n", tok_type_to_str[tok->type], val);
        } else if (tok->type == JSON_NULL) {
            printf("%s null\n", tok_type_to_str[tok->type]);
        } else {
            printf("%s %c\n", tok_type_to_str[tok->type], tok->character);
        }
    }
}

void free_tokens(const AList_t *tokens) {
    for (size_t i = 0; i < tokens->length; i++) {
        token_t *tok = *(token_t **) array_list_get(tokens, i);
        if (tok->type == JSON_STRING && tok->string != NULL) {
            free(tok->string); tok->string = NULL;
        }

        free(tok); tok = NULL;
    }
}