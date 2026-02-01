#pragma once

#include "array_list.h"

typedef enum {
    BRACE_OPEN,
    BRACE_CLOSE,
    BRACKET_OPEN,
    BRACKET_CLOSE,
    COLON,
    COMMA,
    STRING
} TokenType;

typedef struct Token {
    TokenType type;

    union {
        char character;
        char *string;
    };
} token_t;

char *file_to_string(const char *filename);

AList_t *tokenize(const char *str);
