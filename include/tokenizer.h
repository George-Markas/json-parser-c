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
    TOK_NULL
} Token_Type;

extern const char *token_type_map[];

typedef struct Token {
    Token_Type type;
    char *str;
} token_t;

/**
 * @brief Load the contents of a text file into a string.
 * @param filename The path to the file.
 * @return A pointer to the allocated string buffer.
 * @note The string buffer can be freed with free().
 */
char *file_to_string(const char *filename);

/**
 * @brief Break up the provided string into JSON tokens.
 * @param str The string to be tokenized.
 * @return A pointer to the array list containing the
 * tokens or NULL on error.
 */
AList_t *tokenize(const char *str);