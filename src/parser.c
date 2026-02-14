#include "parser.h"
#include "tokenizer.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//@formatter:off
const char *json_type_map[] = {
    [JSON_OBJECT] =  "JSON_OBJECT",
    [JSON_ARRAY] =   "JSON_ARRAY",
    [JSON_STRING] =  "JSON_STRING",
    [JSON_NUMBER] =  "JSON_NUMBER",
    [JSON_BOOLEAN] = "JSON_BOOLEAN",
    [JSON_NULL] =    "JSON_NULL"
};
//@formatter:on