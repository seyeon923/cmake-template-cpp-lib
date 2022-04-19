cmake_minimum_required(VERSION 3.16)

project(mylib VERSION 1.0.0)
string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

option(EX_OPT_VAR "Example of optional variables" ON)
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# print optional variables
message("")
message("-- Optional Variables --")
message("    EX_OPT_VAR = ${EX_OPT_VAR}")
message("    BUILD_SHARED_LIBS = ${BUILD_SHARED_LIBS}")
message("------------------------")
message("")

configure_file(mylib_config.h.in mylib_config.h)
configure_file(mylib_version.h.in "${PROJECT_BINARY_DIR}/include/mylib/mylib_version.h")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# compiler warning flags interface library
add_library(compiler_warning_flags INTERFACE)
set(GCC_LIKE_CXX "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(MSVC_CXX "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(compiler_warning_flags INTERFACE
    "$<${GCC_LIKE_CXX}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
    "$<${MSVC_CXX}:$<BUILD_INTERFACE:-W3>>")

# Internal Static Library
add_library(InternalStaticLib STATIC "src/internal.cpp")
target_link_libraries(InternalStaticLib PUBLIC compiler_warning_flags)
target_include_directories(InternalStaticLib PRIVATE ${PROJECT_SOURCE_DIR})
set_target_properties(InternalStaticLib PROPERTIES
    POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})

# Project Library
add_library(${PROJECT_NAME} "src/mylib.cpp")
target_link_libraries(${PROJECT_NAME} PRIVATE InternalStaticLib)
target_include_directories(${PROJECT_NAME} PUBLIC 
    "${PROJECT_BINARY_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${PROJECT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR})

if(${BUILD_SHARED_LIBS})
    target_compile_definitions(${PROJECT_NAME} PRIVATE "EXPORT_${PROJECT_NAME_UPPER}")
    target_compile_definitions(${PROJECT_NAME} INTERFACE "IMPORT_${PROJECT_NAME_UPPER}")
endif()

# Installed targets and files
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES 
    "include/mylib.h" 
    "include/mylib.hpp" 
    "${PROJECT_BINARY_DIR}/mylib_config.h"
    DESTINATION include)

add_subdirectory(tests)

# Packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
include(CPack)