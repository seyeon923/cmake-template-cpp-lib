project("${CMAKE_PROJECT_NAME}.CLR" VERSION 1.0.0 LANGUAGES CXX CSharp)

if(NOT MSVC)
    message(FATAL_ERROR "This CMake files only works with MSVC.")
endif()

configure_file(AssemblyInfo.cpp.in AssemblyInfo.cpp)

add_library(${PROJECT_NAME}
    mylib.clr.h
    mylib.clr.cpp

    ${CMAKE_CURRENT_BINARY_DIR}/AssemblyInfo.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE /clr /Zc:twoPhase-)
set_target_properties(${PROJECT_NAME} PROPERTIES COMMON_LANGUAGE_RUNTIME "")

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME})

set(configuration "$<IF:$<CONFIG:Debug>,Debug,Release>")
set(out_dir "${CMAKE_BINARY_DIR}/${configuration}")

macro(copy_clr_reference_dll dest_dir)
    set(clr_dll_name "${PROJECT_NAME}$<$<CONFIG:Debug>:${CMAKE_DEBUG_POSTFIX}>.dll")
    set(clr_reference "${dest_dir}/${clr_dll_name}")
    add_custom_command(OUTPUT ${clr_reference}
        COMMAND cmake -E copy ${out_dir}/${clr_dll_name} ${clr_reference}
        DEPENDS ${PROJECT_NAME})
endmacro()

add_subdirectory(Test-mylib.CLR)