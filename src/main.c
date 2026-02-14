#include <stdio.h>
#include <stdlib.h>
#include "ansi.h"
#include "tokenizer.h"
#include "parser.h"

void print_tokens(AList_t *tokens);

void print_json_values(AList_t *json_values);

int main(void) {
    const char *str = file_to_string("../tests/bare_primitives.txt");

    AList_t *tokens = tokenize(str);

    AList_t *json_values = parse(tokens);
    print_json_values(json_values);

    // print_tokens(tokens);

    free((void *) str);

    return EXIT_SUCCESS;
}

void print_tokens(AList_t *tokens) {
    if (!tokens) return;
    for (size_t i = 0; i < tokens->length; i++) {
        const token_t token = get_token(tokens, i);
        const char *token_str = (token.string.str) ? token.string.str : "";
        printf(GREEN(REGULAR)"%s    "RESET"%s\n", token_type_map[token.type], token_str);
        if (token.string.str) free(token.string.str);
    }
    array_list_delete(tokens);
}

void print_json_values(AList_t *json_values) {
    if (!json_values) return;
    for (size_t i = 0; i < json_values->length; i++) {
        const json_value_t json_value = get_json_value(json_values, i);
        switch (json_value.type) {
            case JSON_STRING:
                printf(CYAN(REGULAR)"%s    "RESET"%s\n", json_type_map[json_value.type], json_value.value.string);
                free(json_value.value.string);
                break;
            case JSON_NUMBER:
                printf(CYAN(REGULAR)"%s    "RESET"%g\n", json_type_map[json_value.type], json_value.value.number);
                break;
            case JSON_BOOLEAN: {
                const char *val = (json_value.value.boolean) ? "true" : "false";
                printf(CYAN(REGULAR)"%s   "RESET"%s\n", json_type_map[json_value.type], val);
                break;
            }
            case JSON_NULL:
                printf(CYAN(REGULAR)"%s      "RESET"null\n", json_type_map[json_value.type]);
                break;
            default:
                printf(CYAN(REGULAR)"Unexpected type:    "RESET"%s\n", json_type_map[json_value.type]);
        }
    }
    array_list_delete(json_values);
}