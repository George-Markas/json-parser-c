#include <stdio.h>
#include <stdlib.h>
#include <tokenizer.h>

void print_tokens(const AList_t *tokens);

void free_tokens(const AList_t *tokens);

int main(void) {
    char *buf = file_to_string("../test.json");
    AList_t *tokens = tokenize(buf);
    free(buf);

    print_tokens(tokens);

    free_tokens(tokens);
    array_list_delete(tokens);
    return 0;
}

void print_tokens(const AList_t *tokens) {
    for (size_t i = 0; i < tokens->length; i++) {
        const char *tok_type_to_str[] = {
            "BRACE_OPEN:   ",
            "BRACE_CLOSE:  ",
            "BRACKET_OPEN: ",
            "BRACKET_CLOSE:",
            "COLON:        ",
            "COMMA:        ",
            "STRING:       "
        };

        const token_t *tok = *(token_t **) array_list_get(tokens, i);
        if (tok->type == STRING && tok->string != NULL) {
            printf("%s %s\n", tok_type_to_str[tok->type], tok->string);
        } else {
            printf("%s %c\n", tok_type_to_str[tok->type], tok->character);
        }
    }
}

void free_tokens(const AList_t *tokens) {
    for (size_t i = 0; i < tokens->length; i++) {
        token_t *tok = *(token_t **) array_list_get(tokens, i);
        if (tok->type == STRING && tok->string != NULL) free(tok->string);
        free(tok);
    }
}
