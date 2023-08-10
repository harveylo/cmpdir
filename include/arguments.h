#ifndef __ARGUMENTS_H__
#define __ARGUMENTS_H__

#include <string>

void displayHelp();

class Arguments{
    public:
        Arguments(const Arguments&) = delete;
        Arguments& operator=(const Arguments&) = delete;
        bool parseArguments(int argc, char** argv);
        std::string getDestination();
        std::string getSource();
        bool isRecursive();
        bool isIgnoreHidden();
        bool isIgnoreSize();
        int getArgumentCount();
        static Arguments& getInstance();
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
        std::string sourceRegexString;
        std::string destinationRegexString;
};

#endif