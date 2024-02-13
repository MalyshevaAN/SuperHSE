cmake_minimum_required(VERSION 3.22)

project(super_hse)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_LIST src/main.cpp src/game.cpp src/scene.cpp src/level_map_scene.cpp
 src/main_menu_scene.cpp src/level_scene.cpp)

include_directories(include)

add_executable(main ${SRC_LIST})
target_link_libraries(main sfml-graphics sfml-window sfml-system)
