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

# if ($<CONFIG:Debug> )
#     SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g3 -O0 --coverage -fprofile-arcs -ftest-coverage")
#     SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g3 -O0 --coverage -fprofile-arcs -ftest-coverage")
#     SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
# endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

# set(OBJECT_DIR ${CMAKE_BINARY_DIR}/src/CMakeFiles/cmpdir.dir)
# # message("-- Object files will be output to: ${OUTPUT_DIR}")

# add_custom_target(gcov
#     COMMAND mkdir -p gcoverage
#     COMMAND ${CMAKE_MAKE_PROGRAM} test
#     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
# )
# add_custom_command(TARGET gcov
#     COMMAND echo "=================== GCOV ===================="
#     COMMAND gcov -b ${CMAKE_SOURCE_DIR}/src/*.cpp -o ${OBJECT_DIR}
#     COMMAND echo "-- Source diretorie: ${CMAKE_SOURCE_DIR}/src/"
#     COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/gcoverage"
#     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/gcoverage
# )

# add_custom_target(lcov
#     COMMAND mkdir -p lcoverage
# )
# add_custom_target(TARGET lcov
#     COMMAND echo "=================== LCOV ===================="
#     COMMAND echo "-- Passing lcov tool under code coverage"
#     COMMAND lcov --capture --directory ../ --output-file lcoverage/main_coverage.info
#     COMMAND echo "-- Generating HTML output files"
#     COMMAND genhtml lcoverage/main_coverage.info --output-directory lcoverage
# )

# Put enable_testing() at the top of top-level CMakeLists.txt file
# to enable testing via visual studio code's 'Run Ctest' button or command
# Recommend to run tests via 'ctest' command in terminal under build directory
enable_testing()
add_subdirectory(src)
add_subdirectory(test)
include(CPack)
