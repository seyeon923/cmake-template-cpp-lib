cmake_minimum_required(VERSION 3.16)

project(mylib VERSION 1.0.0)
string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_DEBUG_POSTFIX d)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

option(EX_OPT_VAR "Example of optional variables" ON)
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
if(WIN32)
    option(INCLUDE_CLR "Include CLR Wrapper Library" ON)
else()
    option(INCLUDE_CLR "Include CLR Wrapper Library" OFF)
endif()

# print optional variables
message("")
message("-- Optional Variables --")
message("    EX_OPT_VAR = ${EX_OPT_VAR}")
message("    BUILD_SHARED_LIBS = ${BUILD_SHARED_LIBS}")
message("------------------------")
message("")

configure_file(mylib_config.h.in mylib_config.h)
configure_file(mylib_version.h.in "${PROJECT_BINARY_DIR}/include/mylib/mylib_version.h")

# compiler warning flags interface library
add_library(compiler_warning_flags INTERFACE)
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(compiler_warning_flags INTERFACE
    "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
    "$<${msvc_cxx}:$<BUILD_INTERFACE:-W4>>")

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
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>"
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>")
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${PROJECT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

if(${BUILD_SHARED_LIBS})
    target_compile_definitions(${PROJECT_NAME} PRIVATE "EXPORT_${PROJECT_NAME_UPPER}")
    target_compile_definitions(${PROJECT_NAME} INTERFACE "IMPORT_${PROJECT_NAME_UPPER}")
endif()

# Installed targets and files and export
set(installable_targets ${PROJECT_NAME} InternalStaticLib compiler_warning_flags)
install(TARGETS ${installable_targets}
    EXPORT "${PROJECT_NAME}Targets"
    RUNTIME DESTINATION bin COMPONENT Runtime
    LIBRARY DESTINATION lib COMPONENT Runtime
    ARCHIVE DESTINATION "lib/${PROJECT_NAME}" COMPONENT Development)
install(FILES 
    "include/mylib/mylib_api.h"
    "include/mylib/mylib.h"
    "include/mylib/mylib.hpp"
    "${PROJECT_BINARY_DIR}/include/mylib/mylib_version.h"
    DESTINATION include/mylib)
install(EXPORT "${PROJECT_NAME}Targets"
    FILE "${PROJECT_NAME}Targets.cmake"
    DESTINATION "lib/cmake/${PROJECT_NAME}")

include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION "lib/cmake/example"
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMinorVersion
)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION "lib/cmake/${PROJECT_NAME}")

export(EXPORT "${PROJECT_NAME}Targets"
    FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake")

add_subdirectory(tests)

if(WIN32 AND ${INCLUDE_CLR})
    add_subdirectory(clr_wrapper)
endif()

# Packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
include(CPack)