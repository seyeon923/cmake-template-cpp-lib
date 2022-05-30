set(TEST_TARGET "Test-${PROJECT_NAME}")

add_executable(${TEST_TARGET} test_mylib.cpp)

set_target_properties(${TEST_TARGET} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

target_link_libraries(${TEST_TARGET} PUBLIC ${PROJECT_NAME})

add_test(NAME Runs COMMAND ${TEST_TARGET})

add_test(NAME Version COMMAND ${TEST_TARGET})
set_tests_properties(Version
    PROPERTIES PASS_REGULAR_EXPRESSION 
    "mylib version: ${PROJECT_VERSION}.*")