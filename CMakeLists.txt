cmake_minimum_required(VERSION 3.20.0)
project(compdir VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

include_directories(include)

file(GLOB_RECURSE SRCS "src/*.cpp")

add_executable(compdir ${SRCS})

set_property(TARGET compdir PROPERTY CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -ferror-limit=0")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
