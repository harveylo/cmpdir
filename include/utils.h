#ifndef __UTILS_H__
#define __UTILS_H__

enum Color{
    RED,
    GREEN,
    YELLOW,
    BLUE,
} ;

#define COLOR_GREEN_FG "\e[1;32m"
#define COLOR_YELLOW_FG "\e[1;33m"
#define COLOR_RED_FG "\e[1;31m"
#define COLOR_BLUE_FG "\e[1;34m"
#define COLOR_RESET "\e[0m"
#define COLORED_DEBUG_TAG COLOR_GREEN_FG "[DEBUG]" COLOR_RESET
#define COLORED_WARNING_TAG  COLOR_YELLOW_FG "[WARNING]" COLOR_RESET
#define COLORED_ERROR_TAG COLOR_RED_FG "[ERROR]" COLOR_RESET
#define COLORED_INFO_TAG COLOR_BLUE_FG "[INFO]" COLOR_RESET
#define DEBUG_TAG "[DEBUG]"
#define WARNING_TAG "[WARNING]"
#define ERROR_TAG "[ERROR]"
#define INFO_TAG "[INFO]"

#define COLORED_PRINT(...) _COLORED_PRINT(__VA_ARGS__,"")
#define _COLORED_PRINT(color,format, ...) printf(color format "%s" COLOR_RESET, __VA_ARGS__)

#define DEBUG_FORMAT_PRINT(tag, ...) if(Arguments::getInstance().isColored())printf(COLORED_##tag " " __VA_ARGS__); else printf(tag " " __VA_ARGS__); printf("\n")

#define PRINT(color,...) if(Arguments::getInstance().isColored())COLORED_PRINT(color,__VA_ARGS__); else printf(__VA_ARGS__)

void colored_print(Color color, const char* format, ...);


#endif