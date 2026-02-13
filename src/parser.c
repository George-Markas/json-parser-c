#include "parser.h"
#include "tokenizer.h"
#include "ansi.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

const char *json_type_map[] = {
    [JSON_OBJECT]  = "JSON_OBJECT",
    [JSON_ARRAY]   = "JSON_ARRAY",
    [JSON_STRING]  = "JSON_STRING",
    [JSON_NUMBER]  = "JSON_NUMBER",
    [JSON_BOOLEAN] = "JSON_BOOLEAN",
    [JSON_NULL]    = "JSON_NULL"
};

AList_t *parse(AList_t *tokens) {
    if (!tokens) return NULL;

    AList_t *json_values = array_list_new(sizeof(json_value_t));
    assert(json_values);

    for (size_t i = 0; i < tokens->length; i++) {
        const token_t token = *(token_t *) array_list_get(tokens, i);
        json_value_t json;
        switch (token.type) {
            case TOK_L_BRACE:
            case TOK_R_BRACE:
            case TOK_L_BRACKET:
            case TOK_R_BRACKET:
            case TOK_COMMA:
            case TOK_COLON:
                printf(MAGENTA(REGULAR)"Skipping %s\n"RESET, token_type_map[token.type]);
                continue;
            case TOK_STRING:
                json.type = JSON_STRING;
                json.value.string = strdup(token.str);
                break;
            case TOK_NUMBER:
                json.type = JSON_NUMBER;
                json.value.number = strtod(token.str, NULL);
                break;
            case TOK_TRUE:
                json.type = JSON_BOOLEAN;
                json.value.boolean = true;
                break;
            case TOK_FALSE:
                json.type = JSON_BOOLEAN;
                json.value.boolean = false;
                break;
            case TOK_NULL:
                json.type = JSON_NULL;
                break;
            default:
                ERROR("Syntax error");
                exit(EXIT_FAILURE);
        }

        array_list_add(json_values, &json);
    }

    return json_values;
}