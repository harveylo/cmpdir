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
    this->source = ".";
    this->sourceRegexString = "";
    this->destinationRegexString = "";
}

void displayHelp(){
    printf("Usage: compdir [OPTION]... [SOURCE] DEST\n");
    printf("Valid options:\n");
    printf("\t-r, --recursive: Recursively compare sub-directories\n");
    printf("\t-h, --ignore-hidden: Ignore hidden files and directories\n");
    printf("\t-S, --ignore-size: Ignore file sizes, only compare file names\n");
    printf("\t-d, --destination: Destination directory\n");
    printf("\t-s, --source: Source directory\n");
    printf("\t-H, --help: Display this help and exit\n");
    printf("\t-x, --source-regex: Regex to match files in source dir\n");
    printf("\t-y, --destination-regex: Regex to match files in destination dir\n");
    printf("When SOURCE is not given, the current directory is used\n");
    printf("SOURCE and DEST can be given in order without option tags\n");
    printf("\tExample: compdir /home/user/source /home/user/destination\n");
    printf("which is equivalent to:\n");
    printf("\tcompdir -s /home/user/source -d /home/user/destination\n");
}

bool Arguments::parseArguments(int argc, char **argv){
    this->originalArguments = argv;
    this->argumentCount = argc;
    const struct option longopts[] = {
        {"recursive", no_argument, NULL, 'r'},
        {"ignore-hidden", no_argument, NULL, 'h'},
        {"ignore-size", no_argument, NULL, 'S'},
        {"destination", required_argument, NULL, 'd'},
        {"source", required_argument, NULL, 's'},
        {"help", no_argument, NULL, 'H'},
        {"source-regex", required_argument, NULL, 'x'},
        {"destination-regex", required_argument, NULL, 'y'},
        {NULL, 0, NULL, 0}
    };
    int c;
    while((c = getopt_long(argc, argv, "-:rhSd:s:", longopts, NULL))!=-1){
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
            case 'x':
                this->sourceRegexString = optarg;
                break;
            case 'y':
                this->destinationRegexString = optarg;
                break;
            case ':':
                std::cout << "Missing argument for " << argv[optind-1] << std::endl;
                return false;
            case '?':
                std::cout << "Unknown argument " << (char)optopt << std::endl;
                return false;
            case 'H':
                return false;
            case 1:
                if(this->destination == "")
                    this->destination = optarg;
                else if(this->source == "."){
                    this -> source = destination;
                    this -> destination = optarg;
                }
                else {
                    std::cout << "Too many directory paths, only 2 paths are allowed" << std::endl;
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
    
#ifdef DEBUG
    std::cout<<"Arguments parsed successfully"<<std::endl;
#endif
    return true;
}

std::string Arguments::getDestination(){
    return this->destination;
}
std::string Arguments::getSource(){
    return this->source;
}
bool Arguments::isRecursive(){
    return this->recursive;
}
bool Arguments::isIgnoreHidden(){
    return this->ignoreHidden;
}
bool Arguments::isIgnoreSize(){
    return this->ignoreSize;
}

int Arguments::getArgumentCount(){
    return this->argumentCount;
}