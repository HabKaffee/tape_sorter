cmake_minimum_required(VERSION 3.20)

project(tape_sorter)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(SOURCES
    src/TapeConfig.cpp
    src/TapeInterface.cpp
    src/TapeSorter.cpp
    main.cpp
)

add_executable(tape_sorter ${SOURCES})
target_compile_options(tape_sorter PRIVATE -O2 -Wall -Wpedantic)
target_link_libraries(tape_sorter PRIVATE -lconfig++)
set(EXECUTABLE_OUTPUT_PATH ./)