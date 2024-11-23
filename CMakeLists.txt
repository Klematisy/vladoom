cmake_minimum_required(VERSION 3.31)
project(vladoom)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER /usr/local/bin/g++-14)

find_package(OpenGL REQUIRED)
include_directories(vladoom "Header files/")
include_directories(vladoom "Source files/")
include_directories(vladoom Dependencies/include/)

add_compile_options(-w -g -framework OpenGL)

add_executable(vladoom
    "Source files/convert.cpp"
    "Source files/Cube.cpp"
    "Source files/Door.cpp"
    "Source files/EBO.cpp"
    "Source files/game.cpp"
    "Source files/glew.c"
    "Source files/inputs.cpp"
    "Source files/main.cpp"
    "Source files/Plane.cpp"
    "Source files/programShader.cpp"
    "Source files/solve.cpp"
    "Source files/stb.cpp"
    "Source files/Texture.cpp"
    "Source files/VAO.cpp"
    "Source files/VBO.cpp"
    "Source files/VPlane.cpp"
)

find_library(GLFW_LIB glfw PATHS ${CMAKE_SOURCE_DIR}/Dependencies/library)

if(GLFW_LIB)
    message(STATUS "Found library: ${EXAMPLE_LIB}")
    target_link_libraries(vladoom PRIVATE ${GLFW_LIB})
else()
    message(FATAL_ERROR "Library 'libglfw.3.4' not found.")
endif()

target_link_libraries(vladoom PRIVATE OpenGL::GL)