cmake_minimum_required(VERSION 3.22)

project(super_hse)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(LDtkLoader 1.5.2)

set(SRC_LIST src/main.cpp src/game.cpp src/scene.cpp src/level_map_scene.cpp
 src/main_menu_scene.cpp src/level_scene.cpp src/player.cpp src/Level.cpp 
 src/TileMap.cpp src/hse_utils.cpp src/coin.cpp src/level_icon.cpp src/authentication_scene.cpp
 src/login_scene.cpp src/register_scene.cpp)

include_directories(main include)

add_executable(main ${SRC_LIST})
target_link_libraries(main LDtkLoader sfml-graphics sfml-window sfml-system)
