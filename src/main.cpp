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

    std::string source = std::filesystem::path(arguments.getSource());
    std::string destination = std::filesystem::path(arguments.getDestination());


#ifdef DEBUG
    auto abs_source = std::filesystem::absolute(source);
    auto abs_destination = std::filesystem::absolute(destination);
    DEBUG_FORMAT_PRINT(INFO_TAG, "Source: %s", abs_source.c_str());
    DEBUG_FORMAT_PRINT(INFO_TAG, "Destination: %s", abs_destination.c_str());
    DEBUG_FORMAT_PRINT(INFO_TAG, "PatternString: %s", arguments.getPatternString().c_str());
#endif
    
    if(!std::filesystem::exists(source)||!std::filesystem::is_directory(source)){
        DEBUG_FORMAT_PRINT(ERROR_TAG, "Source directory \"%s\" does not exist or it's not a directory", source.c_str());
        displayHelp();
        return 1;
    }
    if(!std::filesystem::exists(destination)||!std::filesystem::is_directory(destination)){
        DEBUG_FORMAT_PRINT(ERROR_TAG, "Destination directory \"%s\" does not exist or it's not a directory", destination.c_str());
        displayHelp();
        return 1;
    }

    initialize_regex();

    handle_directory(source, destination, 0);
}
