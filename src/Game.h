////////////////////////////////////////////////////////////
//
//  squarly-hoop
//	Copyright (C) 2016  Pampu Andrei (aka. Woky) (andrei.sergiu98@gmail.com)
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////

#ifndef SFMLGAME_ENGINE_H
#define SFMLGAME_ENGINE_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "EntityManager.h"
#include "menu/Menu.h"
#include "music/Music.h"
#include "Score.h"
#include "Mouse.h"
#include "Background.h"
#include "Highscore.h"

enum GameState {
    INGAME, INMENU, GAMEOVER, PAUSED
};

class Game {

public:
    Game();

    void start();

private:
    void loop();

    void renderGame();

    void process();

    void inputProcess();

    void menuHandler();

    void loadTextures();

    void updateGame();

    void updateMenu();

    void renderMenu();

    void restart();

    std::shared_ptr<sf::RenderWindow> window;

    sf::Clock frameClock;

    sf::Time frameTime;

    GameState gameState;

    TextureManager texture;

    Background background;

    Player player;

    Score score;

    Menu menu;

    Music music;

    Highscore highscore;

    EntityManager entities;

    Mouse mouse;

    bool screenShaking;

    sf::Clock screenShackingTime;

    sf::Clock clickSleep;
};


#endif //SFMLGAME_ENGINE_H
