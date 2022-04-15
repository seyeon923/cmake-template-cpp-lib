cmake_minimum_required(VERSION 3.16)

project(mylib VERSION 1.0)

option(EX_OPT_VAR "Example of Optional Variables" ON)

# print optional variables
message("")
message("-- Optional Variables --")
message("    EX_OPT_VAR = ${EX_OPT_VAR}")
message("------------------------")
message("")

configure_file(mylib_config.h.in mylib_config.h)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(${PROJECT_NAME} 
    "src/mylib.cpp" 
    "src/internal.cpp")
    
target_include_directories(${PROJECT_NAME} PUBLIC 
    ${PROJECT_BINARY_DIR}
    "${PROJECT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})

add_subdirectory(tests)