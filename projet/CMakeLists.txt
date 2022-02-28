cmake_minimum_required(VERSION 3.13)
project(projet)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB test_src "include/*.hpp" "src/*.cpp" "test/*.cpp")
add_executable(test test/test_main.cpp ${test_src})

file(GLOB visualisation_src "include/*.hpp" "src/*.cpp" "src/visualisation/*.cpp")
add_executable(visualisation src/visualisation/visualisation_main.cpp ${visualisation_src})
