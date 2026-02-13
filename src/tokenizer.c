#include "tokenizer.h"
#include "utf-8.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

const char *token_type_map[] = {
    [TOK_L_BRACE]   = "TOK_L_BRACE",
    [TOK_R_BRACE]   = "TOK_R_BRACE",
    [TOK_L_BRACKET] = "TOK_L_BRACKET",
    [TOK_R_BRACKET] = "TOK_R_BRACKET",
    [TOK_COLON]     = "TOK_COLON",
    [TOK_COMMA]     = "TOK_COMMA",
    [TOK_STRING]    = "TOK_STRING",
    [TOK_NUMBER]    = "TOK_NUMBER",
    [TOK_TRUE]      = "TOK_TRUE",
    [TOK_FALSE]     = "TOK_FALSE",
    [TOK_NULL]      = "TOK_NULL"
};

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

    __attribute__((unused)) int read = (int) fread(buffer, 1, size, f);

    buffer[size] = '\0';
    fclose(f);

    return buffer;
}

AList_t *tokenize(const char *str) {
    if (!str) return NULL;

    AList_t *tokens = array_list_new(sizeof(token_t));
    assert(tokens);

    u8char_t ch;
    size_t length;

    while (((length = u8_next(str, &ch))) && ch != '\0') {
        token_t token = { .str = NULL };

        switch (ch) {
            case ' ':
            case '\t':
            case '\n':
            case '\r':
                str++; // Ignore whitespaces
                continue;
            case '{': token.type = TOK_L_BRACE; break;
            case '}': token.type = TOK_R_BRACE; break;
            case '[': token.type = TOK_L_BRACKET; break;
            case ']': token.type = TOK_R_BRACKET; break;
            case ':': token.type = TOK_COLON; break;
            case ',': token.type = TOK_COMMA; break;

            /* String */
            case '"': {
                str++; // Skip opening quotes

                const char *start = str;
                while (((length = u8_next(str, &ch))) && ch != '"' && ch != '\0') str += length;
                const size_t string_length = str - start;

                token.type = TOK_STRING;
                token.str = malloc(string_length + 1);
                assert(token.str);
                strlcpy(token.str, start, string_length + 1);
                str++; // Skip closing quotes
                break;
            }

            default:
                /* Number */
                if (isdigit(ch) || ch == '-') {
                    const char *start = str;
                    if (ch == '-') str++; // Skip sign
                    while (u8_next(str, &ch) && (isdigit(ch) || ch == '.' ||
                        ch == 'e' || ch == 'E' ||
                        ch == '+' || ch == '-')) str++;
                    const size_t string_length = str - start;

                    token.type = TOK_NUMBER;
                    token.str = malloc(string_length + 1);
                    assert(token.str);
                    strlcpy(token.str, start, string_length + 1);
                    break;
                }

                /* True */
                if (!strncmp(str, "true", 4)) {
                    token.type = TOK_TRUE;
                    str += 4;
                    break;
                }

                /* False */
                if (!strncmp(str, "false", 5)) {
                    token.type = TOK_FALSE;
                    str += 5;
                    break;
                }

                /* Null */
                if (!strncmp(str, "null", 4)) {
                    token.type = TOK_NULL;
                    str += 4;
                    break;
                }

                ERROR("Unexpected token '%s'", str);
                return NULL;
        }

        array_list_add(tokens, &token);
        str += length;
    }

    return tokens;
}