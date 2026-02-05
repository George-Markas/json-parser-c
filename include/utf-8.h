#pragma once

#include <stdint.h>

typedef uint32_t u8char_t;

int u8_next(const char *str, u8char_t *ch);

u8char_t u8_encode(uint32_t codepoint);

uint32_t u8_decode(u8char_t ch);

#ifndef NDEBUG
void u8_info(u8char_t ch);
#endif
