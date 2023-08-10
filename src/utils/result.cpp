#include <filesystem>
#include "result.h"
#include <cstdint>
#include <cstdio>
#include "utils.h"

Result::Result(){
    this->status = 0;
    this->source = "";
    this->destination = "";
    this->level = 0;
}
Result::Result(uint64_t level) : level(level){} 
void Result::print(){
    print_prefix(this->level);
    if(this->status < 0){
        printf(
            #ifdef COLORED_OUTPUT
                COLOR_RED_FG
            #endif
            "- %s%s\n"
            #ifdef COLORED_OUTPUT
                COLOR_RESET
            #endif
            , this->source.c_str(),(isDirectory?" (folder)":"")
        );
    }else if(this->status > 0){
        printf(
            #ifdef COLORED_OUTPUT
                COLOR_GREEN_FG
            #endif
            "+ %s%s\n"
            #ifdef COLORED_OUTPUT
                COLOR_RESET
            #endif
            , this->destination.c_str(), (isDirectory?" (folder)":"")
        );
    }else{
        printf(
            #ifdef COLORED_OUTPUT
                COLOR_YELLOW_FG
            #endif
            "~ %s%s\n"
            #ifdef COLORED_OUTPUT
                COLOR_RESET
            #endif
            , this->source.c_str(), (isDirectory?" (folder)":"")
        );
    }
}

ResultList::ResultList():Result(){
    this->results = std::vector<Result>();
}
ResultList::ResultList(uint64_t level):Result(level){
    this->results = std::vector<Result>();
}

void ResultList::print(){
    for(auto& result: this->results){
        result.print();
    }
}