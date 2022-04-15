set(TEST_TARGET "Test-${PROJECT_NAME}")

add_executable(${TEST_TARGET} test_mylib.cpp)

target_link_libraries(${TEST_TARGET} PUBLIC ${PROJECT_NAME})

enable_testing()

add_test(NAME Runs COMMAND ${TEST_TARGET})

add_test(NAME Version COMMAND ${TEST_TARGET})
set_tests_properties(Version
    PROPERTIES PASS_REGULAR_EXPRESSION 
    "mylib version: ${${PROJECT_NAME}_VERSION}.*")