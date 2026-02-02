#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

const char *token_type_to_str[] = {
    "TOK_L_BRACE  ",
    "TOK_R_BRACE  ",
    "TOK_L_BRACKET",
    "TOK_R_BRACKET",
    "TOK_COLON    ",
    "TOK_COMMA    ",
    "TOK_STRING:  ",
    "TOK_NUMBER:  ",
    "TOK_TRUE     ",
    "TOK_FALSE    ",
    "TOK_NULL     ",
};

char *file_to_string(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Could not open file '%s'\n", filename);
        exit(EXIT_FAILURE);
    }

    fseek(f, 0, SEEK_END);
    const long size = ftell(f);
    rewind(f);

    char *buffer = malloc(size + 1);
    assert(buffer);

    fread(buffer, 1, size, f);
    buffer[size] = '\0';
    fclose(f);

    return buffer;
}

static token_t *alloc_token(const Token_Type type) {
    token_t *token = malloc(sizeof(token_t));
    assert(token);
    token->type = type;
    token->str = NULL;

    return token;
}

void free_tokens(AList_t *tokens) {
    if (!tokens) return;
    for (size_t i = 0; i < tokens->length; i++) {
        token_t *token = *(token_t **) array_list_get(tokens, i);
        if (token->str) {
            free(token->str); token->str = NULL;
        }

        free(token); token = NULL;
    }

    array_list_delete(tokens);
}

AList_t *tokenizer(const char *str) {
    if (!str) return NULL;

    AList_t *tokens = array_list_new(sizeof(token_t *));
    assert(tokens);

    while (*str != '\0') {
        token_t *token;

        if (*str == '{') {
            token = alloc_token(TOK_L_BRACE);
            array_list_add(tokens, &token);
            str++;
            continue;
        }

        if (*str == '}') {
            token = alloc_token(TOK_R_BRACE);
            array_list_add(tokens, &token);
            str++;
            continue;
        }

        if (*str == '[') {
            token = alloc_token(TOK_L_BRACKET);
            array_list_add(tokens, &token);
            str++;
            continue;
        }

        if (*str == ']') {
            token = alloc_token(TOK_R_BRACKET);
            array_list_add(tokens, &token);
            str++;
            continue;
        }

        if (*str == ':') {
            token = alloc_token(TOK_COLON);
            array_list_add(tokens, &token);
            str++;
            continue;
        }

        if (*str == ',') {
            token = alloc_token(TOK_COMMA);
            array_list_add(tokens, &token);
            str++;
            continue;
        }

        /* Ignore whitespaces */
        if (*str == ' ' || *str == '\n' || *str == '\r' || *str == '\t') {
            str++;
            continue;
        }

        /* String */
        if (*str == '"') {
            str++; // Skip opening quotes

            // Calculate string length
            const char *start = str;
            while (*str != '"' && *str != '\0') str++;
            const size_t length = str - start;

            token = alloc_token(TOK_STRING);
            token->str = strndup(start, length);
            array_list_add(tokens, &token);

            str++; // Skip closing quotes
            continue;
        }

        /* Number */
        if (isdigit(*str) || *str == '-') {
            // Calculate the number's length in digits
            const char *start = str;
            if (*str == '-') str++; // Skip sign
            while (isdigit(*str) || *str == '.' || *str == 'e' || *str == 'E' ||
                   *str == '+' || *str == '-')
                str++;
            const size_t length = str - start;

            token = alloc_token(TOK_NUMBER);
            token->str = strndup(start, length);
            array_list_add(tokens, &token);
            continue;
        }

        /* Boolean */
        if (!strncmp(str, "true", 4)) {
            token = alloc_token(TOK_TRUE);
            array_list_add(tokens, &token);
            str += 4;
            continue;
        } else if (!strncmp(str, "false", 5)) {
            token = alloc_token(TOK_FALSE);
            array_list_add(tokens, &token);
            str += 5;
            continue;
        }

        /* Null */
        if (!strncmp(str, "null", 4)) {
            token = alloc_token(TOK_NULL);
            array_list_add(tokens, &token);
            str += 4;
            continue;
        }

        // On error, fail
        fprintf(stderr, "Unexpected token '%s'\n", str);

        return NULL;
    }

    return tokens;
}
