cmake_minimum_required(VERSION 3.28)
project(pixel_poem)
set(CMAKE_CXX_STANDARD 20)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(pixel_poem main.cpp entities/player/Player.cpp core/game/Game.cpp entities/enemy/Enemy.cpp
        entities/weapon/Weapon.cpp
        entities/bullet/Bullet.h
        entities/bullet/Bullet.cpp
        entities/player/Player.h
        systems/input/Input.h
        systems/input/Input.cpp
        entities/weapon/Weapon.h
        Utils.h
        Utils.h
        Utils.h
        systems/menu/Menu.h
        systems/menu/Menu.cpp
        core/config.h
        systems/ui/UI.cpp
        systems/ui/UI.h)
target_link_libraries(pixel_poem sfml-graphics sfml-audio)
install(TARGETS pixel_poem DESTINATION /usr/local/bin)
