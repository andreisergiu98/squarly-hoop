cmake_minimum_required(VERSION 3.3)
project(sfmlGame)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/home/andrei/Documents/Clion/sfmlGame/bin")

set(SOURCE_FILES src/Game.cpp src/Game.h src/LoadSettings.cpp src/LoadSettings.h src/Player.cpp src/Player.h src/TextureManager.cpp src/TextureManager.h
        src/Bullet.cpp src/Bullet.h src/Enemy.cpp src/Enemy.h src/EntityManager.cpp src/EntityManager.h src/Explosion.cpp src/Explosion.h src/Utilities.h
        src/Utilities.cpp src/ShootingPaterns.h src/ShootingPaterns.cpp src/menu/Menu.cpp src/menu/Menu.h src/menu/Button.cpp src/menu/Button.h src/Score.cpp
        src/Score.h src/music/SoundController.cpp src/music/SoundController.h src/music/Music.cpp src/music/Music.h src/DebugHelper.h src/Mouse.cpp src/Mouse.h src/Background.cpp src/Background.h src/Highscore.cpp src/Highscore.h src/music/Sound.cpp src/music/Sound.h)

set(EXECUTABLE_NAME "sfmlGame")

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif ()

find_package(FMOD REQUIRED)
include_directories(${FMOD_INCLUDE_DIRS})
target_link_libraries(${EXECUTABLE_NAME} ${FMOD_LIBRARIES})
