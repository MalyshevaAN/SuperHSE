cmake_minimum_required(VERSION 3.22)

project(super_hse)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(LDtkLoader 1.5.2)
find_package(SQLite3)

# set (CMAKE_PREFIX_PATH "/")
# find_package(box2d REQUIRED)

set(SRC_LIST src/main.cpp src/sql.cpp src/game.cpp src/scene.cpp src/level_map_scene.cpp src/wardrobe_scene.cpp
 src/main_menu_scene.cpp src/level_scene.cpp src/player.cpp src/Level.cpp 
 src/TileMap.cpp src/hse_utils.cpp src/coin.cpp src/level_icon.cpp src/authentication_scene.cpp
 src/login_scene.cpp src/register_scene.cpp src/enemy.cpp src/lose_scene.cpp src/win_scene.cpp
 src/input_box.cpp src/multiplayer_scene.cpp network/game_client.cpp)

include_directories(super_hse include)

add_executable(super_hse ${SRC_LIST})
target_link_libraries(super_hse LDtkLoader sfml-graphics sfml-window sfml-system sfml-audio sfml-network ${SQLite3_LIBRARIES})


add_executable(server network/game_server.cpp)
target_link_libraries(server sfml-system sfml-graphics sfml-network)

if (SQLITE3_FOUND)
    include_directories(${SQLITE3_INCLUDE_DIRS})
endif (SQLITE3_FOUND)
