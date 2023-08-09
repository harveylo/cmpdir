#include <iostream>
#include "arguments.h"


int main(int argc, char** argv){
    Arguments arguments;
    if(!arguments.parseArguments(argc, argv)){
        displayHelp();
        return 1;
    }
    
}
