#pragma once

#include <stdbool.h>
#include <array_list.h>

#define GET_NEXT_TOKEN(tokens) get_token(tokens, curr_tok); curr_tok++

typedef struct Json_Value {
    enum {
        JSON_OBJECT,
        JSON_ARRAY,
        JSON_STRING,
        JSON_NUMBER,
        JSON_BOOLEAN,
        JSON_NULL,
        JSON_ERROR
    } type;

    union {
        AList_t *elements; // For objects and arrays
        char *string;
        double number;
        bool boolean;
        int error;
    } value;
} json_value_t;

typedef enum {
    JSON_INVALID_LIST = -1,
    JSON_OUT_OF_BOUNDS = -2,
    JSON_RETRIEVAL_FAILED = -3
} Json_Value_Error;

// TODO: Probably need to make a hash table for this
typedef struct Object_Element {
    const char *key;
    json_value_t value;
} object_element_t;

extern const char *json_type_map[];

json_value_t get_json_value(AList_t *json_values, size_t index);

AList_t *parse(AList_t *tokens);