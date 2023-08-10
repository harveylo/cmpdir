#ifndef __UTILS_H__
#define __UTILS_H__

#define COLORED_OUTPUT

#ifdef COLORED_OUTPUT
#define COLOR_GREEN_FG "\e[1;32m"
#define COLOR_YELLOW_FG "\e[1;33m"
#define COLOR_RED_FG "\e[1;31m"
#define COLOR_BLUE_FG "\e[1;34m"
#define COLOR_RESET "\e[0m"
#define DEBUG_TAG COLOR_GREEN_FG "[DEBUG]" COLOR_RESET
#define WARNING_TAG  COLOR_YELLOW_FG "[WARNING]" COLOR_RESET
#define ERROR_TAG COLOR_RED_FG "[ERROR]" COLOR_RESET
#define INFO_TAG COLOR_BLUE_FG "[INFO]" COLOR_RESET
# else 
#define DEBUG_TAG "[DEBUG]"
#define WARNING_TAG "[WARNING]"
#define ERROR_TAG "[ERROR]"
#define INFO_TAG "[INFO]"
#endif

#define DEBUG_FORMAT_PRINT(tag, ...) printf(tag " " __VA_ARGS__); printf("\n")

#endif