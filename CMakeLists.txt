cmake_minimum_required(VERSION 3.27)
project(GameTestC__)

set(CMAKE_CXX_STANDARD 23)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)


add_executable(GameTestC__ main.cpp)

target_link_libraries(GameTestC__ sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
