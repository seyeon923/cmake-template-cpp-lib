cmake_minimum_required(VERSION 3.16)

project(mylib VERSION 1.0.0)

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

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES 
    "include/mylib.h" 
    "include/mylib.hpp" 
    "${PROJECT_BINARY_DIR}/mylib_config.h"
    DESTINATION include)

add_subdirectory(tests)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
include(CPack)