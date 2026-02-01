#pragma once

#include "array_list.h"

typedef enum {
    BRACE_OPEN,
    BRACE_CLOSE,
    BRACKET_OPEN,
    BRACKET_CLOSE,
    COLON,
    COMMA,
    JSON_STRING,
    JSON_NUMBER,
    JSON_BOOLEAN,
    JSON_NULL,
} TokenType;

typedef struct Token {
    TokenType type;

    union {
        char character;
        char *string;
        bool boolean;
        double number;
    };
} token_t;

char *file_to_string(const char *filename);

AList_t *tokenizer(const char *str);
