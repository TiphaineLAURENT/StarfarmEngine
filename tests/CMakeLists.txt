add_executable(tests main.cpp ${ENGINE_SOURCES})
target_link_libraries(tests coverage_config)

add_test(NAME exec_tests COMMAND tests --success)
