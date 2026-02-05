#include "utf-8.h"
#include <stdbool.h>
#include <errno.h>

#ifndef NDEBUG
#include <stdio.h>
#endif

#define U8_LENGTH(str) u8_length[(((uint8_t *)(str))[0] & 0xFF) >> 4]

//@formatter:off
static uint8_t const u8_length[] = {
 /* 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F */
    1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 2, 3, 4
};
//@formatter:on

static bool u8_is_valid(const u8char_t ch) {
    // U+0000 - U+007F
    if (ch <= 0x7F) return true;

    // Validate U+0080 - U+07FF
    if (0xC280 <= ch && ch <= 0xDFBF) return (ch & 0xE0C0) == 0xC080;

    // Reject UTF-16 surrogates
    if (0xEDA080 <= ch && ch <= 0xEDBFBF) return false;

    // U+0800 - U+FFFF
    if (0xE0A080 <= ch && ch <= 0xEFBFBF) return (ch & 0xF0C0C0) == 0xE08080;

    // U+10000 - U+10FFFF
    if (0xF0908080 <= ch && ch <= 0xF48FBFBF)
        return (ch & 0xF8C0C0C0) == 0xF0808080;

    return false;
}

int u8_next(const char *str, u8char_t *ch) {
    u8char_t encoding = 0;
    int length = U8_LENGTH(str);

    for (int i = 0; i < length && str[i] != '\0'; i++) {
        encoding = encoding << 8 | (str[i] & 0xFF);
    }

    errno = 0;
    if (length == 0 || !u8_is_valid(encoding)) {
        encoding = (unsigned char) str[0];
        length = 1;
        errno = EINVAL;
    }

    if (ch) *ch = encoding;

    return encoding ? length : 0;
}

u8char_t u8_encode(const uint32_t codepoint) {
    u8char_t ch = codepoint;

    if (codepoint > 0x7F) {
        ch = (codepoint & 0x000003F) |
             (codepoint & 0x0000FC0) << 2 |
             (codepoint & 0x003F000) << 4 |
             (codepoint & 0x01C0000) << 6;

        if (codepoint < 0x0000800) {
            ch |= 0x0000C080;
        } else if (codepoint < 0x0010000) {
            ch |= 0x00E08080;
        } else {
            ch |= 0xF0808080;
        }
    }

    return ch;
}

uint32_t u8_decode(u8char_t ch) {
    if (ch > 0x7F) {
        const uint32_t mask = ch <= 0x00EFBFBF ? 0x000F0000 : 0x003F0000;
        ch = (ch & 0x07000000) >> 6 |
             (ch & mask) >> 4 |
             (ch & 0x00003F00) >> 2 |
             (ch & 0x0000003F);
    }

    return ch;
}

#ifndef NDEBUG
void u8_info(const u8char_t ch) {
    int length;

    if ((ch >> 24) & 0xFF) length = 4;
    else if ((ch >> 16) & 0xFF) length = 3;
    else if ((ch >> 8) & 0xFF) length = 2;
    else length = 1;

    char bytes[5] = {0};
    for (int i = 0; i < length; i++) {
        bytes[i] = (char) ((ch >> (8 * (length - 1 - i))) & 0xFF);
    }

    printf("UTF-8 encoding:    0x%08X\n"
           "Unicode codepoint: U+%04X\n"
           "Glyph:             '%s'\n\n",
           u8_decode(ch), ch, bytes);
}
#endif
