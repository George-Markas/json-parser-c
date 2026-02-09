#pragma once

#define REGULAR "0"
#define BOLD "1"
#define ITALIC "3"
#define UNDERLINE "4"

#define BLACK(style)   "\x1B[" style ";30m"
#define RED(style)     "\x1B[" style ";31m"
#define GREEN(style)   "\x1B[" style ";32m"
#define YELLOW(style)  "\x1B[" style ";33m"
#define BLUE(style)    "\x1B[" style ";34m"
#define MAGENTA(style) "\x1B[" style ";35m"
#define CYAN(style)    "\x1B[" style ";36m"
#define WHITE(style)   "\x1B[" style ";37m"

#define RESET          "\x1B[0m"