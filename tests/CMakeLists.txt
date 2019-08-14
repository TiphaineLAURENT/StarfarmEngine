set(TEST_EXECUTABLE tests)

add_executable(${TEST_EXECUTABLE} ${ENGINE_SOURCES} main.cpp)
if (WIN32)
    add_custom_command(TARGET ${TEST_EXECUTABLE} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${SFML_DLLS}
                       ${EXECUTABLE_OUTPUT_PATH}
                       )
endif()

target_link_libraries(${TEST_EXECUTABLE} sfml-graphics sfml-audio sfml-window sfml-network sfml-system)
target_link_libraries(${TEST_EXECUTABLE} ecs)
target_link_libraries(${TEST_EXECUTABLE} coverage_config)
install(TARGETS ${TEST_EXECUTABLE} DESTINATION ${EXECUTABLE_OUTPUT_PATH})

add_test(NAME exec_tests COMMAND ${TEST_EXECUTABLE} --success)
