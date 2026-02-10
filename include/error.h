#pragma once

#define MAX_LENGTH 128

#define ERROR(...) error(__FILE__, __LINE__, __VA_ARGS__)

void error(const char *file, int line,  const char *error_message, ...);

void not_implemented(const char *feature);