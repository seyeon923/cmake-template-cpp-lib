set(target_name "Test-${PROJECT_NAME}")

copy_clr_reference_dll(${CMAKE_CURRENT_SOURCE_DIR}/reference_dll)

add_custom_target(${target_name} ALL 
    dotnet build -o ${out_dir} -c ${configuration}
    DEPENDS ${clr_reference}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    SOURCES Program.cs ${target_name}.csproj)

add_custom_command(TARGET ${target_name} PRE_BUILD
    COMMAND cmake -E rm -rf bin
    COMMAND cmake -E rm -rf obj
    COMMAND cmake -E rm -rf reference_dll
    COMMAND dotnet clean -o ${out_dir} -c ${configuration}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_test(NAME "Run ${target_name}"
    COMMAND ${out_dir}/${target_name}.exe)