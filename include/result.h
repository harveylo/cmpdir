#ifndef __RESULT_H__
#define __RESULT_H__

#include <cstdint>
#include <string>
#include <vector>

class Result{
    public:
        Result() = default;
        Result(int status, std::string source, std::string destination, uint64_t numberOfFiles);
        Result(int status, std::string source, std::string destination, uint64_t numberOfFiles, uint64_t level);
        virtual ~Result() = default;
        virtual void print();
    private:
        int status;
        std::string source;
        std::string destination;
        uint64_t numberOfFiles;
        uint64_t level;
};


class ResultList: public Result{
    public:
        ResultList() = default;
        virtual ~ResultList() = default;
        virtual void print();
        std::vector<Result>& getResults();
    private:
        std::vector<Result> results;
};


#endif