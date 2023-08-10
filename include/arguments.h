#ifndef __ARGUMENTS_H__
#define __ARGUMENTS_H__

#include <string>

void displayHelp();

class Arguments{
    public:
        Arguments(const Arguments&) = delete;
        Arguments& operator=(const Arguments&) = delete;
        bool parseArguments(int argc, char** argv);
        std::string getDestination(){
            return this->destination;
        }
        std::string getSource(){
            return this->source;
        }
        bool isRecursive(){
            return this->recursive;
        }
        bool isIgnoreHidden(){
            return this->ignoreHidden;
        }
        bool isIgnoreSize(){
            return this->ignoreSize;
        }
        int getArgumentCount(){
            return this->argumentCount;
        }
        static Arguments& getInstance(){
            static Arguments instance;
            return instance;
        }
        std::string getPatternString(){
            return this->patternString;
        }
    private:
        Arguments();
        ~Arguments() = default;
        char** originalArguments;
        int argumentCount;
        std::string destination;
        std::string source;
        bool recursive;
        bool ignoreHidden;
        bool ignoreSize;
        std::string patternString;
};

#endif