cmake_minimum_required(VERSION 2.8)

project(fql)
set (CMAKE_CXX_STANDARD 11)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

add_library(bird ${CMAKE_SOURCE_DIR}/src/flappybird/bird.cpp)
add_library(game ${CMAKE_SOURCE_DIR}/src/flappybird/game.cpp)

target_link_libraries(game
${SDL2_LIBRARIES} 
${SDL2IMAGE_LIBRARIES}
bird
)

add_executable(app ${CMAKE_SOURCE_DIR}/src/main.cpp)

target_link_libraries(app
${SDL2_LIBRARIES} 
${SDL2IMAGE_LIBRARIES}
game
)
