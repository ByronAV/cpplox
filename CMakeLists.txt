cmake_minimum_required(VERSION 3.26)

project(CPPLOX)

set(CMAKE_CXX_STANDARD 20)

# Set binary path
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

file(GLOB sources "src/*.cpp")
foreach(file ${sources})
    set(SOURCES ${file}) 
endforeach()

set(INCLUDE_DIRECTORIES
    src/include
)

add_executable(cpplox main.cpp ${SOURCES})

target_include_directories(cpplox PRIVATE ${INCLUDE_DIRECTORIES})