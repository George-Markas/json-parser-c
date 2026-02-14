#pragma once

#include <stdbool.h>
#include <array_list.h>

typedef struct Json_Value {
    enum {
        JSON_OBJECT,
        JSON_ARRAY,
        JSON_STRING,
        JSON_NUMBER,
        JSON_BOOLEAN,
        JSON_NULL
    } type;

    union {
        AList_t *elements; // For objects and arrays
        char *string;
        double number;
        bool boolean;
    } value;
} json_value_t;

// TODO: Probably need to make a hash table for this
typedef struct Object_Element {
    const char *key;
    json_value_t value;
} object_element_t;

extern const char *json_type_map[];

