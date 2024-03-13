cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_FLAG -Wall -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

include(FetchContent)

project(CPPLOX)

# Set binary path
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(SOURCES
    src/Run.cpp
    src/Token.cpp
    src/Scanner.cpp
    src/Expr.cpp
)

set(INCLUDE_DIRECTORIES src/includes)

# Fetch the latest version of `fmt` and include it
FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG master
)
FetchContent_MakeAvailable(fmt)

# Fetch the latest version of `robin_hood` and include it
FetchContent_Declare(robin_hood
  GIT_REPOSITORY https://github.com/martinus/robin-hood-hashing.git
  GIT_TAG master
)
FetchContent_MakeAvailable(robin_hood)

add_executable(cpplox main.cpp ${SOURCES} ${INCLUDE_DIRECTORIES})

target_compile_options(cpplox PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_include_directories(cpplox PRIVATE ${INCLUDE_DIRECTORIES})
target_link_libraries(cpplox PRIVATE fmt::fmt robin_hood::robin_hood)

## Testing
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(tests tests/unit_tests/test_token.cpp ${SOURCES} ${INCLUDE_DIRECTORIES})
target_include_directories(tests PRIVATE ${INCLUDE_DIRECTORIES})
target_link_libraries(tests PRIVATE fmt::fmt robin_hood::robin_hood gtest_main)
enable_testing()
add_test(NAME UnitTests COMMAND tests)
