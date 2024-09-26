cmake_minimum_required(VERSION 3.29)
project(pixel_poem)
set(CMAKE_CXX_STANDARD 20)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(
        pixel_poem main.cpp
)
target_link_libraries(pixel_poem sfml-graphics sfml-audio)