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

struct Json_Object_Element {
    char *key;
    struct Json_Value *value;
};

typedef struct Json_Value {
    Json_Value_Type type;

    union {
        struct {
            struct Json_Object_Element **elements;
            size_t count;
        } object;

        struct {
            struct Json_Value **elements;
            size_t count;
        } array;

        char *string;
        double number;
        bool boolean;
    };
} json_value_t;