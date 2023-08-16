
# Add GoogleTest framework
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)
include_directories(${GTEST_INCLUDE_DIRS})
# include_directories(build/_dep/googletst-src/googletest/include)
# include_directories(build/_dep/googltest-src/googlemock/include)


add_executable(arguments_test arguments_test.cpp ../src/utils/arguments.cpp ../src/utils/utils.cpp)
target_link_libraries(
    arguments_test 
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(arguments_test)