#include "utils.h"
#include <cstring>
#include <stdarg.h>
#include <stdio.h>
#include "arguments.h"


static void format_build(char* buf, const char* format, const char* color){
    strcat(buf,color);
    strcat(buf, format);
    strcat(buf, COLOR_RESET);
}

void colored_print(Color color, const char* format, ...){
    va_list args;
    va_start(args, format);
    if(Arguments::getInstance().isColored()){
        char buf[1000]={'\0'};
        switch(color){
            case RED:
                format_build(buf, format, COLOR_RED_FG);
                vfprintf(stdout, buf, args);
                break;
            case GREEN:
                format_build(buf, format, COLOR_GREEN_FG);
                vfprintf(stdout, buf, args);
                break;
            case YELLOW:
                format_build(buf, format, COLOR_YELLOW_FG);
                vfprintf(stdout, buf, args);
                break;
            case BLUE:
                format_build(buf, format, COLOR_BLUE_FG);
                vfprintf(stdout, buf, args);
                break;
        }
    }else vfprintf(stdout, format, args);
    va_end(args);
}