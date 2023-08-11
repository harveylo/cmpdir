#ifndef __RESULT_H__
#define __RESULT_H__

#include "utils.h"
#include <cstddef>
#include <cstdint>
#include <vector>
#include <filesystem>

class Result{
    public:
        Result();
        Result(uint64_t level);
        virtual ~Result() = default;
        virtual void print();
        int status;
        bool isDirectory;
        std::filesystem::directory_entry source;
        std::filesystem::directory_entry destination;
        uint64_t level;
        static void print_prefix(uint64_t level){
            if(level == 0) return;
            for(uint64_t i = 0; i < level; i++){
                printf(" ");
            }
            printf("|_");
        }
    private:
        void general_print(Color);
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
        void addResult(std::filesystem::directory_entry* source, std::filesystem::directory_entry* destination, int status, bool isDirectory){
            Result result(this->level+1);
            if(source )result.source = *source;
            if(destination)result.destination = *destination;
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