#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef enum {
    JSON_OBJECT,
    JSON_ARRAY,
    JSON_STRING,
    JSON_NUMBER,
    JSON_BOOLEAN,
    JSON_NULL
} Json_Value_Type;

typedef struct JsonValue {
    Json_Value_Type type;

    union {
        struct {
            char **keys;
            struct JsonValue **values;
            size_t count;
        } object;

        struct {
            struct JsonValue **elements;
            size_t count;
        } array;

        char *string;
        double number;
        bool boolean;
    };
} json_value_t;