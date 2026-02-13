#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ansi.h"
#include "tokenizer.h"
#include "parser.h"

void print_tokens(AList_t *tokens);

void print_json_values(AList_t *json_values);

int main(void) {
    const char *str = file_to_string("../tests/json_types.txt");

    AList_t *tokens = tokenize(str);
    assert(tokens);

    AList_t *json_values = parse(tokens);
    assert(json_values);

    print_tokens(tokens);
    print_json_values(json_values);

    free((void *) str);

    return EXIT_SUCCESS;
}

void print_tokens(AList_t *tokens) {
    for (size_t i = 0; i < tokens->length; i++) {
        const token_t token = *(token_t *) array_list_get(tokens, i);
        const char *token_str = (token.str) ? token.str : "";
        printf(GREEN(REGULAR)"%s "RESET"%s\n", token_type_map[token.type], token_str);
        if (token.str) free(token.str);
    }
    putchar('\n');
    array_list_delete(tokens);
}

void print_json_values(AList_t *json_values) {
    for (size_t i = 0; i < json_values->length; i++) {
        const json_value_t json = *(json_value_t *) array_list_get(json_values, i);
        switch (json.type) {
            case JSON_STRING:
                printf(CYAN(REGULAR)"%s "RESET"'%s'\n", json_type_map[json.type], json.value.string);
                free(json.value.string);
                break;
            case JSON_NUMBER:
                printf(CYAN(REGULAR)"%s "RESET"%g\n", json_type_map[json.type], json.value.number);
                break;
            case JSON_BOOLEAN: {
                const char *value = (json.value.boolean) ? "true" : "false";
                printf(CYAN(REGULAR)"%s "RESET"%s\n", json_type_map[json.type], value);
                break;
            }
            case JSON_NULL:
                printf(CYAN(REGULAR)"%s "RESET"null\n", json_type_map[json.type]);
                break;
            default:
                printf("Unknown type\n");
        }
    }
    putchar('\n');
    array_list_delete(json_values);
}