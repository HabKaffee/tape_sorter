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

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

add_executable(tape_sorter ${SOURCES})
target_compile_options(tape_sorter PRIVATE -O2 -Wall -Wpedantic)
target_link_libraries(tape_sorter PRIVATE -lconfig++)
set(EXECUTABLE_OUTPUT_PATH ./)

enable_testing()
find_package(GTest REQUIRED)

add_executable(
  tests
  tests/TapeSorterTest.cpp
  src/TapeConfig.cpp
  src/TapeInterface.cpp
  src/TapeSorter.cpp
)

target_link_libraries(
  tests
  GTest::gtest
  GTest::gtest_main
  -lconfig++
)
add_test(AllTests tests)

add_custom_command(TARGET tests
    POST_BUILD
    COMMAND ./tests
)


# include(GoogleTest)
# gtest_discover_tests(hello_test)