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
        AList_t *elements; // For both objects and arrays
        char *string;
        double number;
        bool boolean;
    } value;
} json_value_t;

void dummy_parse(const char *filename);
