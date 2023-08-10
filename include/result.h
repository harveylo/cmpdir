#ifndef __RESULT_H__
#define __RESULT_H__

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

class Result{
    public:
        Result();
        Result(uint64_t level);
        virtual ~Result() = default;
        virtual void print();
        int status;
        bool isDirectory;
        std::string source;
        std::string destination;
        uint64_t level;
        static void print_prefix(uint64_t level){
            if(level == 0) return;
            for(uint64_t i = 0; i < level; i++){
                printf(" ");
            }
            printf("|_");
        }
};


class ResultList: public Result{
    public:
        ResultList();
        ResultList(uint64_t level);
        virtual ~ResultList() = default;
        virtual void print();
        std::vector<Result>& getResults(){
            return this->results;
        }
        void addResult(std::string source, std::string destination, int status, bool isDirectory){
            Result result(this->level+1);
            result.source = source;
            result.destination = destination;
            result.status = status;
            result.isDirectory = isDirectory;
            results.emplace_back(result);
        }
        void sort(){
            std::sort(results.begin(), results.end(), [](const Result& a, const Result& b){
                return a.status < b.status;
            });
        }
        size_t size(){
            return this->results.size();
        }
    protected:
        std::vector<Result> results;
};


#endif