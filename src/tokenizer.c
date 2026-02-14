#include "tokenizer.h"
#include "utf-8.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

//@formatter:off
const char *token_type_map[] = {
    [TOKEN_L_BRACE] =   "TOKEN_L_BRACE",
    [TOKEN_R_BRACE] =   "TOKEN_R_BRACE",
    [TOKEN_L_BRACKET] = "TOKEN_L_BRACKET",
    [TOKEN_R_BRACKET] = "TOKEN_R_BRACKET",
    [TOKEN_COLON] =     "TOKEN_COLON",
    [TOKEN_COMMA] =     "TOKEN_COMMA",
    [TOKEN_STRING] =    "TOKEN_STRING",
    [TOKEN_NUMBER] =    "TOKEN_NUMBER",
    [TOKEN_TRUE] =      "TOKEN_TRUE",
    [TOKEN_FALSE] =     "TOKEN_FALSE",
    [TOKEN_NULL] =      "TOKEN_NULL",
    [TOKEN_ERROR] =     "TOKEN_ERROR",
};

const char *token_error_map[] = {
    [-1 * TOKEN_INVALID_LIST]     = "Invalid token list",
    [-1 * TOKEN_OUT_OF_BOUNDS]    = "Out of bounds token index",
    [-1 * TOKEN_RETRIEVAL_FAILED] = "Could not get token",
    [-1 * TOKEN_UNEXPECTED_TOKEN] = "Unexpected token"
};
//@formatter:on

char *file_to_string(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        ERROR("Could not open file '%s'", filename);
        exit(EXIT_FAILURE);
    }

    fseek(f, 0, SEEK_END);
    const long size = ftell(f);
    rewind(f);

    char *buffer = malloc(size + 1);
    assert(buffer);

    // Hush the compiler
    __attribute__((unused)) size_t read = fread(buffer, 1, size, f);

    buffer[size] = '\0';
    fclose(f);

    return buffer;
}

token_t get_token(AList_t *tokens, const size_t index) {
    if (!tokens)
        return (token_t) {
            .type = TOKEN_ERROR,
            .error = TOKEN_INVALID_LIST
        };

    if (index >= tokens->length)
        return (token_t) {
            .type = TOKEN_ERROR,
            .error = TOKEN_OUT_OF_BOUNDS
        };

    // Avoid dereferencing NULL
    token_t *token = array_list_get(tokens, index);
    if (!token)
        return (token_t) {
            .type = TOKEN_ERROR,
            .error = TOKEN_RETRIEVAL_FAILED
        };

    return *token;
}

AList_t *tokenize(const char *str) {
    if (!str) return NULL;

    AList_t *tokens = array_list_new(sizeof(token_t));
    assert(tokens);

    u8char_t ch;
    size_t length;

    while ((length = u8_next(str, &ch)) && ch != '\0') {
        token_t token = {
            .string = {
                .str = NULL,
                .length = 0
            }
        };

        switch (ch) {
            case ' ':
            case '\t':
            case '\n':
            case '\r':
                str++; // Ignore whitespaces
                continue;

            //@formatter:off
            case '{': token.type = TOKEN_L_BRACE;   break;
            case '}': token.type = TOKEN_R_BRACE;   break;
            case '[': token.type = TOKEN_L_BRACKET; break;
            case ']': token.type = TOKEN_R_BRACKET; break;
            case ':': token.type = TOKEN_COLON;     break;
            case ',': token.type = TOKEN_COMMA;     break;
            //@formatter:on

            /* String */
            case '"': {
                str++; // Skip opening quotes

                const char *start = str;
                while ((length = u8_next(str, &ch)) && ch != '"' && ch != '\0') str += length;
                const size_t string_length = str - start;

                token.type = TOKEN_STRING;
                token.string.str = malloc(string_length + 1);
                token.string.length = string_length;
                assert(token.string.str);
                strlcpy(token.string.str, start, string_length + 1);

                str++; // Skip closing quotes
                break;
            }

            default:
                /* Number */
                if (isdigit(ch) || ch == '-') {
                    const char *start = str;
                    if (ch == '-') str++; // Skip sign

                    //@formatter:off
                    while (u8_next(str, &ch) && (isdigit(ch) || ch == '.' ||
                                                   ch == 'e' || ch == 'E' ||
                                                   ch == '+' || ch == '-')) str++;
                    //@formatter:on
                    const size_t string_length = str - start;

                    token.type = TOKEN_NUMBER;
                    token.string.str = malloc(string_length + 1);
                    token.string.length = string_length;
                    assert(token.string.str);
                    strlcpy(token.string.str, start, string_length + 1);
                    break;
                }

                /* True */
                if (!strncmp(str, "true", 4)) {
                    token.type = TOKEN_TRUE;
                    str += 4;
                    break;
                }

                /* False */
                if (!strncmp(str, "false", 5)) {
                    token.type = TOKEN_FALSE;
                    str += 5;
                    break;
                }

                /* Null */
                if (!strncmp(str, "null", 4)) {
                    token.type = TOKEN_NULL;
                    str += 4;
                    break;
                }

                ERROR("Unexpected token '%s'", str);
                goto cleanup;
        }

        array_list_add(tokens, &token);
        str += length;
    }

    return tokens;

cleanup:
    for (size_t i = 0; i < tokens->length; i++) {
        const token_t token = get_token(tokens, i);
        if (token.type == TOKEN_ERROR) {
            ERROR("%s", token_error_map[token.error]);
            exit(EXIT_FAILURE);
        }
        if (token.string.str) free(token.string.str);
    }

    array_list_delete(tokens);
    return NULL;
}