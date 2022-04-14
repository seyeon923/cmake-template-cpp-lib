set(TEST_TARGET "Test-${PROJECT_NAME}")

add_executable(${TEST_TARGET} test_mylib.cpp)

target_link_libraries(${TEST_TARGET} PUBLIC ${PROJECT_NAME})