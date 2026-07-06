cmake_minimum_required(VERSION 3.10)
project(TileHexaV3)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(TileHexaV3
    Hexa3DApp.cpp
    TileSolver.cpp
)

target_link_libraries(TileHexaV3
    sfml-graphics sfml-window sfml-system
    OpenGL::GL
    glfw
)
