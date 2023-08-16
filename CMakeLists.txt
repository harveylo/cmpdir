cmake_minimum_required(VERSION 3.20.0)
project(cmpdir VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

# SET(CMAKE_CXX_COMPILER clang++)
# SET(CMAKE_C_COMPILE clang)
SET(CMAKE_CXX_STANDARD 20)


include_directories(include)



# set_property(TARGET cmpdir PROPERTY CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall  -ferror-limit=0")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g3 -O0 --coverage -fprofile-arcs -ftest-coverage")
add_compile_definitions(
    $<$<CONFIG:Debug>:DEBUG>
)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

SET(BUILD ${CMAKE_BINARY_DIR})
SET(ROOT ${CMAKE_SOURCE_DIR})

add_custom_target(cov_report
    COMMAND ctest
    COMMAND echo "=================== LCOV ===================="
    COMMAND lcov --capture --d ${ROOT}/src 
    -d ${ROOT}/include -d ${BUILD}/test -t test 
    -b ${BUILD}/test -o ${BUILD}/test/cover.info 
    --rc lcov_branch_coverage=1 --no-external
    COMMAND echo "-- Generating HTML output files"
    COMMAND genhtml ${BUILD}/test/cover.info -o ${BUILD}/report --rc genhtml_branch_coverage=1
)

# Put enable_testing() at the top of top-level CMakeLists.txt file
# to enable testing via visual studio code's 'Run Ctest' button or command
# Recommend to run tests via 'ctest' command in terminal under build directory
enable_testing()
add_subdirectory(src)
add_subdirectory(test)
include(CPack)
