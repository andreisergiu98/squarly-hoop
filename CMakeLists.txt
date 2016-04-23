cmake_minimum_required(VERSION 3.5)

project(squarly-hoop)

set(EXECUTABLE_NAME "squarly-hoop")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/")

set(SOURCE_FILES src/Game.cpp src/Game.h src/LoadSettings.cpp src/LoadSettings.h src/Player.cpp src/Player.h src/TextureManager.cpp src/TextureManager.h
        src/Bullet.cpp src/Bullet.h src/Enemy.cpp src/Enemy.h src/EntityManager.cpp src/EntityManager.h src/Explosion.cpp src/Explosion.h src/Utilities.h
        src/Utilities.cpp src/ShootingPaterns.h src/ShootingPaterns.cpp src/menu/Menu.cpp src/menu/Menu.h src/menu/Button.cpp src/menu/Button.h src/Score.cpp
        src/Score.h src/sound/SoundController.cpp src/sound/SoundController.h src/sound/Music.cpp src/sound/Music.h src/DebugHelper.h src/Mouse.cpp src/Mouse.h
        src/Background.cpp src/Background.h src/Highscore.cpp src/Highscore.h src/sound/Sound.cpp src/sound/Sound.h src/Particle.cpp src/Particle.h)

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

include_directories(/usr/include/SFML/)
include_directories(/usr/include/fmodex/)
include_directories(/usr/include/boost/)
link_directories(/usr/lib/)

target_link_libraries(${EXECUTABLE_NAME} sfml-system sfml-window sfml-graphics boost_system boost_filesystem fmodex)