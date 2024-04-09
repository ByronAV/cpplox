set(TEST_SOURCES
    unit_tests/test_token.cpp
    unit_tests/test_scanner.cpp)

FetchContent_Declare(googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

add_executable(unit_tests ${TEST_SOURCES} ${SOURCES} ${INCLUDE_DIRECTORIES} )
target_include_directories(unit_tests PRIVATE ${INCLUDE_DIRECTORIES})
target_link_libraries(unit_tests PRIVATE fmt::fmt robin_hood::robin_hood gtest_main)
enable_testing()
add_test(NAME UnitTests COMMAND unit_tests)
