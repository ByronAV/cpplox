cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

project(CPPLOX)

# Set binary path
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(SOURCES
    src/Run.cpp
    src/Error.cpp
    src/Token.cpp
    src/Scanner.cpp
)

set(INCLUDE_DIRECTORIES
    src/include
)

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

add_executable(cpplox main.cpp ${SOURCES})

target_compile_options(cpplox PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_include_directories(cpplox PRIVATE ${INCLUDE_DIRECTORIES})
target_link_libraries(cpplox PRIVATE fmt::fmt robin_hood::robin_hood)
