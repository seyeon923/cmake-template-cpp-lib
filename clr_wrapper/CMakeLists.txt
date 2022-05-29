project("${CMAKE_PROJECT_NAME}.CLR" VERSION 1.0.0 LANGUAGES CXX CSharp)

if(NOT MSVC)
    message(FATAL_ERROR "This CMake files only works with MSVC.")
endif()

configure_file(AssemblyInfo.cpp.in AssemblyInfo.cpp)

add_library(${PROJECT_NAME} 
    mylib.clr.h
    mylib.clr.cpp
    
    ${CMAKE_CURRENT_BINARY_DIR}/AssemblyInfo.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES COMMON_LANGUAGE_RUNTIME "")

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME} compiler_warning_flags)