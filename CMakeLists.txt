cmake_minimum_required(VERSION 3.28)
project(pixel_poem)
set(CMAKE_CXX_STANDARD 20)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(pixel_poem main.cpp player/Player.cpp game/Game.cpp enemy/Enemy.cpp
        weapon/Weapon.cpp
        bullet/Bullet.h
        bullet/Bullet.cpp
        player/Player.h
        input/Input.h
        input/Input.cpp
        weapon/Weapon.h
        Utils.h
        Utils.h
        Utils.h)
target_link_libraries(pixel_poem sfml-graphics sfml-audio)
install(TARGETS pixel_poem DESTINATION /usr/local/bin)
