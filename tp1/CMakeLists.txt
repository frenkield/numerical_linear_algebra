cmake_minimum_required(VERSION 3.13)
project(tp1)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB test_src "include/*.hpp" "src/*.cpp" "test/*.cpp")
add_executable(test test/test_main.cpp ${test_src})

file(GLOB exercices_src "include/*.hpp" "src/*.cpp" "src/exercices/*.cpp")
add_executable(exercices src/exercices/exercices_main.cpp ${exercices_src})
