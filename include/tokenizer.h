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
} Token_Type;

typedef struct Token {
    Token_Type type;
    char *str;
} token_t;

// Convenient array lookup to get the token type as a string
extern const char *token_type_to_str[];

/**
 * @brief Load the contents of a text file into a string.
 * @param filename The path to the file.
 * @return A pointer to the allocated string buffer.
 * @note The string buffer can be freed with free().
 */
char *file_to_string(const char *filename);

/**
 * @brief Break up the provided string into JSON tokens.
 * @param str The string of the text to be tokenized.
 * @return An array list containing the tokens.
 */
AList_t *tokenizer(const char *str);

/**
 * @brief Free any allocated tokens and the array list that contains them.
 * @param tokens The array list containing the tokens.
 */
void free_tokens(AList_t *tokens);
