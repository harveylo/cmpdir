
file(GLOB_RECURSE SRCS "*.cpp")

add_executable(cmpdir ${SRCS})

set_target_properties(cmpdir PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")