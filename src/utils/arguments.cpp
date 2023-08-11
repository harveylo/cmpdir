#include "arguments.h"
#include <cstdio>
#include <iostream>
#include <getopt.h>
#include "utils.h"


Arguments::Arguments(){
    recursive = false;
    ignoreHidden = false;
    ignoreSize = false;
    destination = "";
    source = "";
    patternString= "";
    colored = true;
}


void displayHelp(){
    printf("Usage: cmpdir [OPTION]... [SOURCE] DEST [PATTERN]\n");
    printf("Valid options:\n");
    printf("\t-r, --recursive: Recursively compare sub-directories\n");
    printf("\t-h, --ignore-hidden: Ignore hidden files and directories\n");
    printf("\t-S, --ignore-size: Ignore file sizes, only compare file names\n");
    printf("\t-d, --destination: Destination directory\n");
    printf("\t-s, --source: Source directory\n");
    printf("\t-H, --help: Display this help and exit\n");
    printf("\t-p, --pattern: Regex pattern to match file names\n");
    printf("\t-c, --color-off: Disable colored output\n");
    printf("\t-v, --verbose: Print verbose information.\n");
    printf("When SOURCE is not given, the current directory is used\n");
    printf("SOURCE and DEST can be given in order without option tags\n");
    printf("\tExample: compdir /home/user/source /home/user/destination\n");
    printf("\twhich is equivalent to:\n");
    printf("\tcompdir -s /home/user/source -d /home/user/destination\n");
}

bool Arguments::parseArguments(int argc, char **argv){
    originalArguments = argv;
    argumentCount = argc-1;
    const struct option longopts[] = {
        {"recursive", no_argument, NULL, 'r'},
        {"ignore-hidden", no_argument, NULL, 'h'},
        {"ignore-size", no_argument, NULL, 'S'},
        {"destination", required_argument, NULL, 'd'},
        {"source", required_argument, NULL, 's'},
        {"help", no_argument, NULL, 'H'},
        {"pattern", required_argument, NULL, 'p'},
        {"color-off", no_argument, NULL, 'c'},
        {"verbose", no_argument, NULL, 'v'},
        {NULL, 0, NULL, 0}
    };
    int c;
    while((c = getopt_long(argc, argv, "-:rhcSHvd:s:p:", longopts, NULL))!=-1){
        switch(c){
            case 'r':
                recursive = true;
                break;
            case 'h':
                ignoreHidden = true;
                break;
            case 'S':
                ignoreSize = true;
                break;
            case 'd':
                destination = optarg;
                break;
            case 's':
                source = optarg;
                break;
            case 'p':
                patternString = optarg;
                break;
            case ':':
                std::cout << "Missing argument for '" << argv[optind-1]<<"'" << std::endl;
                return false;
            case '?':
                std::cout << "Unknown argument '" << (char)optopt <<"'"<< std::endl;
                return false;
            case 'H':
                return false;
            case 'c':
                colored = false;
                break;
            case 'v':
                verbose = true;
                break;
            case 1:
                if(destination == "")
                    destination = optarg;
                else if(source == ""){
                    this -> source = destination;
                    this -> destination = optarg;
                }
                else if(patternString==""){
                    patternString = optarg;
                }
                else {
                    std::cout << "Too many directory paths and regex patterns, only 2 paths and 1 pattern are allowed" << std::endl;
                    return false;
                }
                break;
            default:
                std::cout << "Unknown error" << std::endl;
                return false;
        }
    }
    if(destination == ""){
        std::cout << "Destination path is required" << std::endl;
        return false;
    }
    if(this -> source == ""){
        this -> source = ".";
    }
    if(patternString == ""){
        patternString = ".*";
    }
    
#ifdef DEBUG
    DEBUG_FORMAT_PRINT(DEBUG_TAG, "%d arguments parsed successfully", argumentCount);
#endif
    return true;
}
