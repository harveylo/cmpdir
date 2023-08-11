#include <filesystem>
#include "result.h"
#include <cstdint>
#include <cstdio>
#include "utils.h"
#include "arguments.h"




std::unordered_map<uint64_t,int> Result::prefix_map = std::unordered_map<uint64_t,int>();

Result::Result(){
    this->status = 0;
    this->level = 0;
}
Result::Result(uint64_t level) : level(level){} 
void Result::print(){
    print_prefix(level);
    if(this->status < 0){
        if(Arguments::getInstance().isVerbose())
            colored_print(Color::RED, "- %s%s\n" , std::filesystem::absolute(source.path().string()).string().c_str(), (isDirectory?" (folder)":""));
        else 
            colored_print(Color::RED, "- %s%s\n" , source.path().filename().string().c_str(), (isDirectory?" (folder)":""));
    }else if(this->status > 0){
        if(Arguments::getInstance().isVerbose())
            colored_print(Color::GREEN, "+ %s%s\n" , std::filesystem::absolute(destination.path().string()).string().c_str(), (isDirectory?" (folder)":""));
        else 
            colored_print(Color::GREEN, "+ %s%s\n" , destination.path().filename().string().c_str(), (isDirectory?" (folder)":""));
    }else{
        if(Arguments::getInstance().isVerbose())
            colored_print(Color::YELLOW, "~ %s%s\n" , std::filesystem::absolute(source.path().string()).string().c_str(), (isDirectory?" (folder)":""));
        else 
            colored_print(Color::YELLOW, "~ %s%s\n" , source.path().filename().string().c_str(), (isDirectory?" (folder)":""));
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