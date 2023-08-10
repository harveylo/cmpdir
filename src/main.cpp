#include <cstdio>
#include <filesystem>
#include <iostream>
#include <string>
#include "arguments.h"
#include "utils.h"
#include "workload.h"


int main(int argc, char** argv){
    Arguments& arguments = Arguments::getInstance();
    if(!(arguments.parseArguments(argc, argv))){
        displayHelp();
        return 1;
    }

    std::string source = arguments.getSource();
    std::string destination = arguments.getDestination();

    auto abs_source = std::filesystem::absolute(source);
    auto abs_destination = std::filesystem::absolute(destination);

#ifdef DEBUG
    DEBUG_FORMAT_PRINT(INFO_TAG, "Source: %s", abs_source.c_str());
    DEBUG_FORMAT_PRINT(INFO_TAG, "Destination: %s", abs_destination.c_str());
    DEBUG_FORMAT_PRINT(INFO_TAG, "PatternString: %s", arguments.getPatternString().c_str());
#endif
    
    if(!std::filesystem::exists(abs_source)||!std::filesystem::is_directory(abs_source)){
        DEBUG_FORMAT_PRINT(ERROR_TAG, "Source directory does not exist or it's not a directory");
        return 1;
    }
    if(!std::filesystem::exists(abs_destination)||!std::filesystem::is_directory(abs_destination)){
        DEBUG_FORMAT_PRINT(ERROR_TAG, "Destination directory does not exist or it's not a directory");
        return 1;
    }

    initialize_regex();

    handle_directory(abs_source, abs_destination, 0);
}
