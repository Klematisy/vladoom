cmake_minimum_required(VERSION 3.31)
project(vladoom)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)
# set(CMAKE_CXX_COMPILER /usr/local/bin/x86_64-w64-mingw32-g++)
set(CMAKE_CXX_FLAGS "-Werror=vla")

find_package(OpenGL REQUIRED)
include_directories(vladoom "headers/")
include_directories(vladoom "src/ENG/")
include_directories(vladoom "deps/include/")

add_compile_options(-w -g -framework OpenGL)

add_executable(vladoom
    "src/ENG/convert.cpp"
    "src/ENG/Cube.cpp"
    "src/ENG/EBO.cpp"
    "src/ENG/glew.c"
    "src/ENG/Plane.cpp"
    "src/ENG/programShader.cpp"
    "src/ENG/stb.cpp"
    "src/ENG/Texture.cpp"
    "src/ENG/VAO.cpp"
    "src/ENG/VBO.cpp"
    "src/ENG/VPlane.cpp"
    "src/ENG/Symbol.cpp"
    "src/ENG/image.cpp"
    "src/Hud.cpp"
    "src/enemy.cpp"
    "src/inputs.cpp"
    "src/gun.cpp"
    "src/Door.cpp"
    "src/game.cpp"
    "src/main.cpp"
    "src/settings.cpp"
    "src/furniture.cpp"
    "src/item.cpp"
    "src/secret_door.cpp"
    "src/dog.cpp"
    "src/pause.cpp"
    "src/stage1.cpp"
    "src/main_menu.cpp"
    "src/menu.cpp"
)

# find_library(GLFW_LIB glfw PATHS ${CMAKE_SOURCE_DIR}/deps/library/)
target_link_libraries(vladoom ${CMAKE_SOURCE_DIR}/deps/library/libglfw.3.4.dylib)
target_link_libraries(vladoom OpenGL::GL)
# /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/Dependencies/library/libglfw.3.4.dylib

# if(GLFW_LIB)
#     message(STATUS "Found library: ${EXAMPLE_LIB}")
#     target_link_libraries(vladoom PRIVATE ${GLFW_LIB} OpenGL::GL)
# else()
#     message(FATAL_ERROR "Library 'libglfw.3.4' not found.")
# endif()