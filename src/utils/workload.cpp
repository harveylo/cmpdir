#include "utils.h"
#include "workload.h"
#include <filesystem>
#include <vector>
#include "result.h"
#include <regex>
#include "arguments.h"

static std::regex pattern;

void initialize_regex(){
    pattern = std::regex(Arguments::getInstance().getPatternString());
}

static void handle_remaining(int i, std::vector<std::filesystem::directory_entry>& list, ResultList& result_list, int status,Arguments& arguments){
    while(i<list.size()){
        auto& source_entry = list[i];
        if(source_entry.path().filename().string()[0]=='.'&&arguments.isIgnoreHidden()){
            i++;
            continue;
        }
        if(std::regex_match(source_entry.path().filename().string(), pattern)){
            result_list.addResult(
                &source_entry,
                &source_entry,
                status,
                source_entry.is_directory()
            );
        }
        i++;
    }
}
static void handle_mismatch(std::filesystem::directory_entry entry, ResultList& result_list, Arguments& arguments, int status){
    if(entry.path().filename().string()[0]=='.'&&arguments.isIgnoreHidden()) return;
    if(std::regex_match(entry.path().filename().string(), pattern)||entry.is_directory()){
        result_list.addResult(
            &entry,
            &entry,
            status,
            entry.is_directory()
        );
    }
}


void handle_directory(std::filesystem::path source, std::filesystem::path destination, uint64_t level) {
    ResultList result_list(level);
    int count = 0; 
    int dcount = 0;
    Arguments& arguments = Arguments::getInstance();
    bool hasRecurse = false;


    auto source_dir = std::filesystem::directory_iterator(source);
    auto destination_dir = std::filesystem::directory_iterator(destination);
    std::vector<std::filesystem::directory_entry> source_entries;
    std::vector<std::filesystem::directory_entry> destination_entries;
    

    for(auto& entry: source_dir){
        source_entries.push_back(entry);
    }
    for(auto& entry: destination_dir){
        destination_entries.push_back(entry);
    }


    sort(source_entries.begin(), source_entries.end(), [](const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b){
        return a.path().filename().string() < b.path().filename().string();
    });
    sort(destination_entries.begin(), destination_entries.end(), [](const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b){
        return a.path().filename().string() < b.path().filename().string();
    });
    

// #ifdef DEBUG
//     DEBUG_FORMAT_PRINT(INFO_TAG, "Source directory: %s", source.c_str());
//     for(auto& entry: source_entries){
//         printf("%s\n", entry.path().filename().string().c_str());
//     }
//     DEBUG_FORMAT_PRINT(INFO_TAG, "Destination directory: %s", destination.c_str());
//     for(auto& entry: destination_entries){
//         printf("%s\n", entry.path().filename().string().c_str());
//     }
//     printf("\n\n\n\n");
// #endif


    int i = 0,j=0;
    if(level == 0){
        printf("In the base directory\n");
    }else {
        Result::print_prefix(level);
        printf("In the directory: %s\n", source.filename().string().c_str());
    }
    while(i<source_entries.size()&&j<destination_entries.size()){
        auto& source_entry = source_entries[i];
        auto& destination_entry = destination_entries[j];
        if(source_entry.path().filename().string() == destination_entry.path().filename().string()){
            if(source_entry.path().filename().string()[0]=='.'&&arguments.isIgnoreHidden()){
                i++;
                j++;
                continue;
            }
            if(source_entry.is_directory()&&destination_entry.is_directory()){
                if(arguments.isRecursive()){
                        handle_directory(source_entry.path(), destination_entry.path(), level+2);
                        hasRecurse = true; 
                    }
                else dcount++;
            }
            else if(source_entry.is_regular_file()&&destination_entry.is_regular_file()){
                if(std::regex_match(source_entry.path().filename().string(), pattern)){
                    if(!arguments.isIgnoreSize()){
                        if(std::filesystem::file_size(source_entry.path())!=std::filesystem::file_size(destination_entry.path())){
                            result_list.addResult(&source_entry, &destination_entry, 0, false);
                        }else count++;
                    }else count++;
                }
            }
            i++;
            j++;
        }
        else if(source_entry.path().filename().string() < destination_entry.path().filename().string()){
            handle_mismatch(source_entry, result_list, arguments, -1);
            i++;
        }
        else{
            handle_mismatch(destination_entry, result_list, arguments, 1);
            j++;
        }
    }


    // Handle the remaining entries in each directory
    handle_remaining(i, source_entries, result_list, -1, arguments);
    handle_remaining(j, destination_entries, result_list, 1,arguments);


    result_list.sort();


    result_list.print();
    if(count>0){
        Result::print_prefix(level+1);
        printf("%d file(s) %smatched\n", count, arguments.isIgnoreSize()?"name ":"name and size ");
    }
    if(dcount>0){
        Result::print_prefix(level+1);
        printf("%d folder(s) name matched\n", dcount);
    }
    if(result_list.size()==0&&count==0&&dcount==0&&!hasRecurse){
        Result::print_prefix(level+1);
        printf("Empty Folder\n");
    }
}