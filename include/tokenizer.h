#pragma once

#include "array_list.h"

typedef enum {
    TOKEN_L_BRACE,
    TOKEN_R_BRACE,
    TOKEN_L_BRACKET,
    TOKEN_R_BRACKET,
    TOKEN_COLON,
    TOKEN_COMMA,
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_NULL,
    TOKEN_ERROR
} Token_Type;

extern const char *token_type_map[];

typedef enum {
    ERROR_INVALID_LIST = -1,
    ERROR_OUT_OF_BOUNDS = -2,
    ERROR_FAILED_RETRIEVAL = -3,
    ERROR_UNEXPECTED_TOKEN = -4,
} Token_Error;

extern const char *token_error_map[];

typedef struct Token {
    Token_Type type;

    union {
        char *str;
        int error;
    };
} token_t;

/**
 * @brief Load the contents of a text file into a string.
 * @param filename The path to the file.
 * @return A pointer to the allocated string buffer.
 * @note The string buffer can be freed with free().
 */
char *file_to_string(const char *filename);

/**
 * @brief Wrapper for array_list_get() for getting tokens without accidentally
 * dereferencing NULL in case array_list_get() fails.
 * @param tokens The array list containing the tokens.
 * @param index The index of the token.
 * @return The specific token or a token of type TOKEN_ERROR with the corresponding
 * error code.
 */
token_t get_token(AList_t *tokens, size_t index);

/**
 * @brief Break up the provided string into JSON tokens.
 * @param str The string to be tokenized.
 * @return A pointer to the array list containing the
 * tokens or NULL on error.
 */
AList_t *tokenize(const char *str);