#include "arguments.h"
#include <cstdio>
#include <iostream>
#include <getopt.h>
#include "utils.h"


Arguments::Arguments(){
    this->recursive = false;
    this->ignoreHidden = false;
    this->ignoreSize = false;
    this->destination = "";
    this->source = "";
    this->patternString= "";
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
    printf("When SOURCE is not given, the current directory is used\n");
    printf("SOURCE and DEST can be given in order without option tags\n");
    printf("\tExample: compdir /home/user/source /home/user/destination\n");
    printf("\twhich is equivalent to:\n");
    printf("\tcompdir -s /home/user/source -d /home/user/destination\n");
}

bool Arguments::parseArguments(int argc, char **argv){
    this->originalArguments = argv;
    this->argumentCount = argc-1;
    const struct option longopts[] = {
        {"recursive", no_argument, NULL, 'r'},
        {"ignore-hidden", no_argument, NULL, 'h'},
        {"ignore-size", no_argument, NULL, 'S'},
        {"destination", required_argument, NULL, 'd'},
        {"source", required_argument, NULL, 's'},
        {"help", no_argument, NULL, 'H'},
        {"pattern", required_argument, NULL, 'p'},
        {NULL, 0, NULL, 0}
    };
    int c;
    while((c = getopt_long(argc, argv, "-:rhSHd:s:p:", longopts, NULL))!=-1){
        switch(c){
            case 'r':
                this->recursive = true;
                break;
            case 'h':
                this->ignoreHidden = true;
                break;
            case 'S':
                this->ignoreSize = true;
                break;
            case 'd':
                this->destination = optarg;
                break;
            case 's':
                this->source = optarg;
                break;
            case 'p':
                this->patternString = optarg;
                break;
            case ':':
                std::cout << "Missing argument for '" << argv[optind-1]<<"'" << std::endl;
                return false;
            case '?':
                std::cout << "Unknown argument '" << (char)optopt <<"'"<< std::endl;
                return false;
            case 'H':
                return false;
            case 1:
                if(this->destination == "")
                    this->destination = optarg;
                else if(this->source == ""){
                    this -> source = destination;
                    this -> destination = optarg;
                }
                else if(patternString==""){
                    this->patternString = optarg;
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
    if(this->destination == ""){
        std::cout << "Destination path is required" << std::endl;
        return false;
    }
    if(this -> source == ""){
        this -> source = ".";
    }
    if(this->patternString == ""){
        this->patternString = ".*";
    }
    
#ifdef DEBUG
    DEBUG_FORMAT_PRINT(DEBUG_TAG, "%d arguments parsed successfully", this->argumentCount);
#endif
    return true;
}
