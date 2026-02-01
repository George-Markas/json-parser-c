#include "tokenizer.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

char *file_to_string(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Could not open file '%s'\n", filename);
        exit(EXIT_FAILURE);
    }

    fseek(f, 0, SEEK_END);
    const long size = ftell(f);
    rewind(f);

    char *buf = malloc(size + 1);
    if (!buf) {
        fprintf(stderr, "Allocation failed\n");
        exit(EXIT_FAILURE);
    }

    fread(buf, 1, size, f);
    buf[size] = '\0';
    fclose(f);

    return buf;
}

static token_t *alloc_token(const TokenType type) {
    token_t *tok = malloc(sizeof(token_t));
    if (!tok) {
        fprintf(stderr, "Allocation failed\n");
        exit(EXIT_FAILURE);
    }
    tok->type = type;

    return tok;
}

AList_t *tokenize(const char *str) {
    if (!str) return NULL;

    AList_t *tokens = array_list_new(sizeof(token_t *));
    if (!tokens) {
        fprintf(stderr, "Allocation failed\n");
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

        // String
        if (*str == '"') {
            str++; // Skip opening quotes

            // Calculate string length
            const char *start = str;
            while (*str != '"' && *str != '\0') str++;
            const unsigned int length = str - start;

            tok = alloc_token(JSON_STRING);
            tok->string = strndup(start, length);
            array_list_add(tokens, &tok);

            str++; // Skip closing quotes
            continue;
        }

        // Number
        if (isdigit(*str) || *str == '-') {
            tok = alloc_token(JSON_NUMBER);
            char *end;
            tok->number = strtod(str, &end);
            array_list_add(tokens, &tok);
            str = end;
            continue;
        }

        // Boolean
        if (!strncmp(str, "true", 4)) {
            tok = alloc_token(JSON_BOOLEAN);
            tok->boolean = true;
            array_list_add(tokens, &tok);
            str += 4;
            continue;
        } else if (!strncmp(str, "false", 5)) {
            tok = alloc_token(JSON_BOOLEAN);
            tok->boolean = false;
            array_list_add(tokens, &tok);
            str += 5;
            continue;
        }

        // Null
        if (!strncmp(str, "null", 4)) {
            tok = alloc_token(JSON_NULL);
            array_list_add(tokens, &tok);
            str += 4;
            continue;
        }

        fprintf(stderr, "Unexpected token '%s'\n", str);

        return NULL;
    }

    return tokens;
}
