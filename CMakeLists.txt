cmake_minimum_required(VERSION 3.28)

# Имя проекта и стандарт C++
project(pixel_poem)
set(CMAKE_CXX_STANDARD 20)

# Подключение SFML
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# Установка переменных для групп файлов
set(SOURCES
        main.cpp
        core/game/Game.cpp
        entities/player/Player.cpp
        entities/enemy/Enemy.cpp
        entities/weapon/Weapon.cpp
        entities/bullet/Bullet.cpp
        systems/input/Input.cpp
        systems/menu/Menu.cpp
        systems/ui/UI.cpp
        systems/animation/Animation.cpp
        systems/map/Map.cpp
        core/game/GameStateManager.cpp
        entities/entity/EntityManager.cpp
        systems/collision/CollisionManager.cpp
        systems/camera/CameraManager.cpp
        systems/map/MapManager.cpp
        systems/pause/Pause.cpp
        systems/end/End.cpp
        entities/money/Money.cpp
        entities/boss/Boss.cpp
)

set(HEADERS
        core/game/Game.h
        entities/player/Player.h
        entities/enemy/Enemy.h
        entities/weapon/Weapon.h
        entities/bullet/Bullet.h
        systems/input/Input.h
        systems/menu/Menu.h
        systems/ui/UI.h
        systems/animation/Animation.h
        systems/map/Map.h
        Utils.h
        core/config.h
        core/game/GameStateManager.h
        entities/entity/EntityManager.h
        systems/camera/CameraManager.h
        systems/collision/CollisionManager.h
        systems/map/MapManager.h
        systems/pause/Pause.h
        systems/end/End.h
        entities/money/Money.h
        entities/boss/Boss.h
)

# Добавление исполняемого файла
add_executable(pixel_poem ${SOURCES} ${HEADERS})

# Линковка с SFML
target_link_libraries(pixel_poem sfml-graphics sfml-audio)

# Установка исполняемого файла
install(TARGETS pixel_poem DESTINATION /usr/local/bin)
