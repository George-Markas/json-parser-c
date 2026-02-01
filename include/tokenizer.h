#pragma once

#include "array_list.h"

typedef enum {
    TOK_L_BRACE,
    TOK_R_BRACE,
    TOK_L_BRACKET,
    TOK_R_BRACKET,
    TOK_COLON,
    TOK_COMMA,
    TOK_STRING,
    TOK_NUMBER,
    TOK_TRUE,
    TOK_FALSE,
    TOK_NULL,
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

extern const char *tok_type_to_str[];

char *file_to_string(const char *filename);

AList_t *tokenizer(const char *str);
