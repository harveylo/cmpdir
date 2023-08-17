
file(GLOB EXE_SRCS LIST_DIRECTORIES false "*.cpp")

add_executable(cmpdir ${EXE_SRCS})

file(GLOB_RECURSE UTILS_SRCS  "utils/*.cpp")

add_library(utils_lib SHARED ${UTILS_SRCS})

set(UTILS_SRCS_CACHE ${UTILS_SRCS} CACHE INTERNAL "utils_lib sources files cache")

set_target_properties(cmpdir PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

target_link_libraries(cmpdir utils_lib)