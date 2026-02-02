#include "tokenizer.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char *tok_type_to_str[] = {
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
    tok->str = NULL;

    return tok;
}

AList_t *tokenizer(const char *str) {
    if (!str) return NULL;

    AList_t *tokens = array_list_new(sizeof(token_t *));
    if (!tokens) {
        fprintf(stderr, "Allocation failed\n");
        exit(EXIT_FAILURE);
    }

    while (*str != '\0') {
        token_t *tok;

        if (*str == '{') {
            tok = alloc_token(TOK_L_BRACE);
            array_list_add(tokens, &tok);
            str++;
            continue;
        }

        if (*str == '}') {
            tok = alloc_token(TOK_R_BRACE);
            array_list_add(tokens, &tok);
            str++;
            continue;
        }

        if (*str == '[') {
            tok = alloc_token(TOK_L_BRACKET);
            array_list_add(tokens, &tok);
            str++;
            continue;
        }

        if (*str == ']') {
            tok = alloc_token(TOK_R_BRACKET);
            array_list_add(tokens, &tok);
            str++;
            continue;
        }

        if (*str == ':') {
            tok = alloc_token(TOK_COLON);
            array_list_add(tokens, &tok);
            str++;
            continue;
        }

        if (*str == ',') {
            tok = alloc_token(TOK_COMMA);
            array_list_add(tokens, &tok);
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

            tok = alloc_token(TOK_STRING);
            tok->str = strndup(start, length);
            array_list_add(tokens, &tok);

            str++; // Skip closing quotes
            continue;
        }

        /* Number */
        if (isdigit(*str) || *str == '-') {

            // Calculate the number's length in digits
            const char *start = str;
            if (*str == '-') str++; // Skip sign
            while (isdigit(*str) || *str == '.' || *str == 'e' || *str == 'E' ||
                *str == '+' || *str == '-') str++;
            const size_t length = str - start;

            tok = alloc_token(TOK_NUMBER);
            tok->str = strndup(start, length);
            array_list_add(tokens, &tok);
            continue;
        }

        /* Boolean */
        if (!strncmp(str, "true", 4)) {
            tok = alloc_token(TOK_TRUE);
            array_list_add(tokens, &tok);
            str += 4;
            continue;
        } else if (!strncmp(str, "false", 5)) {
            tok = alloc_token(TOK_FALSE);
            array_list_add(tokens, &tok);
            str += 5;
            continue;
        }

        /* Null */
        if (!strncmp(str, "null", 4)) {
            tok = alloc_token(TOK_NULL);
            array_list_add(tokens, &tok);
            str += 4;
            continue;
        }

        fprintf(stderr, "Unexpected token '%s'\n", str);

        return NULL;
    }

    return tokens;
}
