project("${CMAKE_PROJECT_NAME}.CLR" VERSION 1.0.0 LANGUAGES CXX CSharp)

if(NOT MSVC)
    message(FATAL_ERROR "This CMake files only works with MSVC.")
endif()

configure_file(AssemblyInfo.cpp.in AssemblyInfo.cpp)

add_library(${PROJECT_NAME} 
    mylib.clr.h
    mylib.clr.cpp
    
    ${CMAKE_CURRENT_BINARY_DIR}/AssemblyInfo.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE /clr)
set_target_properties(${PROJECT_NAME} PROPERTIES COMMON_LANGUAGE_RUNTIME "")

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME} compiler_warning_flags)

set(configuration "$<IF:$<CONFIG:Debug>,Debug,Release>")
set(out_dir "${CMAKE_BINARY_DIR}/${configuration}")
macro(copy_clr_reference_dll dest_dir)
    set(clr_reference "${dest_dir}/${configuration}/${PROJECT_NAME}.dll")
    add_custom_command(OUTPUT ${clr_reference}
        COMMAND cmake -e copy ${out_dir}/${PROJECT_NAME}.dll ${clr_reference}
        DEPENDS ${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endmacro()