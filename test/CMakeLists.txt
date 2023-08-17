enable_testing()

# Add GoogleTest framework
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)
include_directories(${GTEST_INCLUDE_DIRS})
# include_directories(build/_deps/googletst-src/googletest/include)
include_directories("${CMAKE_BINARY_DIR}/_deps/googletest-src/googlemock/include")

FILE(GLOB_RECURSE UTILS_TEST_SOURCES "utils/*.cpp")


add_executable(utils_test ${UTILS_TEST_SOURCES} ${UTILS_SRCS_CACHE})
target_link_libraries(
    utils_test 
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(utils_test)