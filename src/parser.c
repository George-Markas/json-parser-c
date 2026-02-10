#include "parser.h"
#include "tokenizer.h"
#include "ansi.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const char *json_type_map[] = {
    [JSON_OBJECT]  = "JSON_OBJECT",
    [JSON_ARRAY]   = "JSON_ARRAY",
    [JSON_STRING]  = "JSON_STRING",
    [JSON_NUMBER]  = "JSON_NUMBER",
    [JSON_BOOLEAN] = "JSON_BOOLEAN",
    [JSON_NULL]    = "JSON_NULL"
};

void dummy_parse(const char *filename) {
    /* The parser has not been implemented yet */

    AList_t *tokens = tokenize(filename);
    assert(tokens);

    for (size_t i = 0; i < tokens->length; i++) {
        const token_t token = *(token_t *) array_list_get(tokens, i);
        const char *token_str = (token.str) ? token.str : "";
        printf(GREEN(REGULAR)"%s"RESET"%s\n", token_type_map[token.type], token_str);
        if (token.str) free(token.str);
    }
    array_list_delete(tokens);
}