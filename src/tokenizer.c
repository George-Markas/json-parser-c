#include "tokenizer.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, size, f);
    buffer[size] = '\0';
    fclose(f);

    return buffer;
}

static token_t *alloc_token(const TokenType type) {
    token_t *tok = malloc(sizeof(token_t));
    if (!tok) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    tok->type = type;

    return tok;
}

AList_t *tokenize(const char *str) {
    if (!str) return NULL;

    AList_t *tokens = array_list_new(sizeof(token_t *));
    if (!tokens) {
        fprintf(stderr, "Could not create array list\n");
        exit(EXIT_FAILURE);
    }

    while (*str != '\0') {
        token_t *tok;

        if (*str == '{') {
            tok = alloc_token(BRACE_OPEN);
            tok->character = *str;
            array_list_add(tokens, &tok);
            str++;
            continue;
        }

        if (*str == '}') {
            tok = alloc_token(BRACE_CLOSE);
            tok->character = *str;
            array_list_add(tokens, &tok);
            str++;
            continue;
        }

        if (*str == '[') {
            tok = alloc_token(BRACKET_OPEN);
            tok->character = *str;
            array_list_add(tokens, &tok);
            str++;
            continue;
        }

        if (*str == ']') {
            tok = alloc_token(BRACKET_CLOSE);
            tok->character = *str;
            array_list_add(tokens, &tok);
            str++;
            continue;
        }

        if (*str == ':') {
            tok = alloc_token(COLON);
            tok->character = *str;
            array_list_add(tokens, &tok);
            str++;
            continue;
        }

        if (*str == ',') {
            tok = alloc_token(COMMA);
            tok->character = *str;
            array_list_add(tokens, &tok);
            str++;
            continue;
        }

        // Ignore whitespaces
        if (*str == ' ' || *str == '\n' || *str == '\r' || *str == '\t') {
            str++;
            continue;
        }

        // if (*str == '"') {
        //     str++; // Skip opening quote
        //
        //     // Calculate string length
        //     const char *temp = str;
        //     while (*str != '"' && *str != '\0') str++;
        //     const unsigned int length = str - temp;
        //
        //     token_t *token = alloc_token(JSON_STRING);
        //     token->string = malloc(sizeof(length + 1));
        //     if (!token->string) {
        //         fprintf(stderr, "Allocation failed\n");
        //         exit(EXIT_FAILURE);
        //     }
        //
        //     strlcpy(token->string, temp, length + 1);
        //     array_list_add(tokens, token);
        //     str++; // Skip closing quote
        //     continue;
        // }

        fprintf(stderr, "Unexpected token '%s'\n", str);

        return NULL;
    }

    return tokens;
}
