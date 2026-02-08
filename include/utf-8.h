#pragma once

#include <stdint.h>

typedef uint32_t u8char_t;

/**
 * Get the next UTF-8 encoding from a string.
 * @param str The string to read from.
 * @param ch Where the encoding will be saved.
 * @return The UTF-8 encoding's byte length.
 * @note Subsequent calls of this function on the same string won't
 * increment the pointer. Do so manually if needed using the returned length.
 */
int u8_next(const char *str, u8char_t *ch);


/**
 * Encode a Unicode codepoint using UTF-8.
 * @param codepoint The Unicode codepoint to encode.
 * @return The encoding.
 */
u8char_t u8_encode(uint32_t codepoint);

/**
 * Decode a UTF-8 encoding.
 * @param ch The UTF-8 encoding to decode.
 * @return The Unicode codepoint.
 */
uint32_t u8_decode(u8char_t ch);

/**
 * Wrapper to register the '%U' format specifier for use with u8char_t in
 * the printf family of functions.
 * @return Zero on success or -1 on error.
 */
int register_uchar8_t_printf(void);

#ifndef NDEBUG
void u8_info(u8char_t ch);
#endif
