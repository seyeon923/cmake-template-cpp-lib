cmake_minimum_required(VERSION 3.16)

project(mylib VERSION 1.0)

option(EXPORT_C_FUNC "Export C Function" ON)

configure_file(mylib_config.h.in mylib_config.h)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(EXPORT_C_FUNC)
    message("Export C Functions")
endif()

add_library(${PROJECT_NAME} src/mylib.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC 
    ${PROJECT_BINARY_DIR}
    "${PROJECT_SOURCE_DIR}/include")

add_subdirectory(tests)