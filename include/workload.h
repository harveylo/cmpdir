#ifndef __WORKLOAD_H__
#define __WORKLOAD_H__
#include "result.h"
#include <cstdint>
#include <filesystem>

void handle_directory(std::filesystem::path source, std::filesystem::path destination, uint64_t level);

void initialize_regex();

#endif