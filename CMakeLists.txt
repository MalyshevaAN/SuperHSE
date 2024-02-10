cmake_minimum_required(VERSION 3.22)

project(super_hse)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_LIST src/main.cpp)

add_executable(main ${SRC_LIST})
target_link_libraries(main sfml-graphics sfml-window sfml-system)
