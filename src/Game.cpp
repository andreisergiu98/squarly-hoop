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

#include "Game.h"
#include "LoadSettings.h"

Game::Game() {
    LoadSettings settings;

    window = settings.set();

    sf::FloatRect windowBounds;
    windowBounds.left = 0;
    windowBounds.top = 0;
    windowBounds.width = window->getSize().x;
    windowBounds.height = window->getSize().y;

    player = Player(windowBounds);

    entities = EntityManager(windowBounds);

    gameState = GameState::INMENU;

    background.setTexture(texture.getTexture("../res/Textures/background.png"));
    background.setPosition(0, 0);
    background.setScale(0.7, 0.8);
}

void Game::process() {
    player.process();
    entities.process();

    frameTime = frameClock.restart();
}

void Game::updateGame() {
    player.update(frameTime);
    player.updateMousePosition(sf::Mouse::getPosition(*window));

    entities.update(frameTime);
    entities.update(player);

    background.setColor(
            sf::Color((sf::Uint8) (rand() % 255 + 0), (sf::Uint8) (rand() % 255 + 0), (sf::Uint8) (rand() % 255 + 0),
                      (sf::Uint8) (rand() % 255 + 0)));
}

void Game::renderGame() {
    window->draw(entities);
    window->draw(player);
}

void Game::loop() {
    sf::Event event;
    while (window->isOpen()) {
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window->close();
                }
            }
        }
        window->clear();

        if (gameState == INGAME) {
            process();
            updateGame();
            renderGame();
        }
        if (gameState == INMENU) {
            menuHandler();
            updateMenu();
            renderMenu();
        }
        if (gameState == GAMEOVER) {
            process();
            menuHandler();
            updateGame();
            updateMenu();
            renderGame();
            renderMenu();
        }

        window->display();
    }
}

void Game::menuHandler() {
    if (gameState == INMENU) {
        if (menu.isPressed(Buttons::PLAY)) {
            restart();
            gameState = INGAME;
        }
        if (menu.isPressed(Buttons::OPTIONS)) {
            //...
        }
        if (menu.isPressed(Buttons::EXIT)) {
            window->close();
        }
    }
    else if (gameState == GAMEOVER) {
        if (menu.isPressed(Buttons::RETRY)) {
            restart();
            gameState = INGAME;
        }
        if (menu.isPressed(Buttons::MENU)) {
            gameState = INMENU;
        }
    }
}

void Game::updateMenu() {
    menu.updateMousePosition(sf::Mouse::getPosition(*window));
    menu.update();
}

void Game::renderMenu() {
    window->draw(menu);
}

void Game::restart() {
    entities.clear();
    //...
}

void Game::start() {
    loop();
}

int main() {
    Game game;

    game.start();

    return EXIT_SUCCESS;
}

