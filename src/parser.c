#include "parser.h"
#include "tokenizer.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//@formatter:off
const char *json_type_map[] = {
    [JSON_OBJECT] =  "JSON_OBJECT",
    [JSON_ARRAY] =   "JSON_ARRAY",
    [JSON_STRING] =  "JSON_STRING",
    [JSON_NUMBER] =  "JSON_NUMBER",
    [JSON_BOOLEAN] = "JSON_BOOLEAN",
    [JSON_NULL] =    "JSON_NULL"
};

const char *json_value_error_map[] = {
    [-1 * JSON_INVALID_LIST]     = "Invalid token list",
    [-1 * JSON_OUT_OF_BOUNDS]    = "Out of bounds json value index",
    [-1 * JSON_RETRIEVAL_FAILED] = "Could not get token",
};
//@formatter:on

json_value_t get_json_value(AList_t *json_values, const size_t index) {
    if (!json_values)
        return (json_value_t) {
            .type = JSON_ERROR,
            .value.error = JSON_INVALID_LIST,
        };

    if (index >= json_values->length)
        return (json_value_t) {
            .type = JSON_ERROR,
            .value.error = JSON_OUT_OF_BOUNDS,
        };

    // Avoid dereferencing NULL
    json_value_t *json_value = array_list_get(json_values, index);
    if (!json_value)
        return (json_value_t) {
            .type = JSON_ERROR,
            .value.error = JSON_RETRIEVAL_FAILED,
        };

    return *json_value;
}

static size_t curr_tok = 0;

json_value_t parse_array(AList_t *tokens);

json_value_t *parse_object(AList_t *tokens);

static json_value_t parse_primitive(const token_t token) {
    json_value_t json_value;

    switch (token.type) {
        case TOKEN_STRING:
            json_value.type = JSON_STRING;
            json_value.value.string = strndup(token.string.str, token.string.length);
            break;
        case TOKEN_NUMBER:
            json_value.type = JSON_NUMBER;
            json_value.value.number = strtod(token.string.str, NULL);
            break;
        case TOKEN_TRUE:
        case TOKEN_FALSE:
            json_value.type = JSON_BOOLEAN;
            json_value.value.boolean = (token.type == TOKEN_TRUE) ? true : false;
            break;
        case TOKEN_NULL:
            json_value.type = JSON_NULL;
            break;
        default:
            ERROR("Expected primitive token, got '%s'", token_type_map[token.type]);
            exit(EXIT_FAILURE);
    }

    return json_value;
}

AList_t *parse(AList_t *tokens) {

    AList_t *json_values = array_list_new(sizeof(json_value_t));
    assert(json_values);

    for (size_t i = 0; i < tokens->length; i++) {
        const token_t token = GET_NEXT_TOKEN(tokens);
        json_value_t json_value = parse_primitive(token);
        array_list_add(json_values, &json_value);
    }

    return json_values;
}