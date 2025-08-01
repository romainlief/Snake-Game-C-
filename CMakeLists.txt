cmake_minimum_required(VERSION 3.27)
project(snake)

set(CMAKE_CXX_STANDARD 23)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)


add_executable(snake main.cpp src/snake.cpp src/game.cpp src/window.cpp)

target_link_libraries(snake sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
