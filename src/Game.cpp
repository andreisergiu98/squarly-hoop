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

    window = settings.load();
    window->setMouseCursorVisible(false);
    texture.setSmoothTextures(settings.smoothTextures());
    loadTextures();

    sf::FloatRect windowBounds;
    windowBounds.left = 0;
    windowBounds.top = 0;
    windowBounds.width = window->getSize().x;
    windowBounds.height = window->getSize().y;

    menu = Menu(windowBounds, &texture);

    player = Player(windowBounds, &texture);

    entities = EntityManager(windowBounds, &texture);

    score = Score(windowBounds);

    mouse = Mouse(&texture.getTexture("../res/textures/cursor.png"));

    gameState = GameState::INMENU;

    background = Background(windowBounds, sf::Vector2f(1920, 3072),
                            &texture.getTexture("../res/textures/background.png"),
                            &texture.getTexture("../res/textures/background1.png"));

    music.loadPlaylist("playlist");

    screenShaking = false;
    miniScreenShaking = false;
}

void Game::process() {
    player.process();
    entities.process();
    background.process();

    if (player.getHp() <= 0) {
        gameState = GameState::GAMEOVER;
        highscore.update(score.getScore());
        player.setPosition(sf::Vector2f(window->getSize().x / 2.f, 4000));
    }
}

void Game::updateGame() {
    player.update(frameTime);
    entities.update(frameTime);
    entities.update(player);
    background.update(frameTime);
    music.update();

    entities.updateBeat(music.getBeat(), music.getFreq());

    score.setScore(score.getScore() + entities.getDestroyedEnemies());

    if (entities.getDestroyedEnemies()) {
        miniScreenShaking = true;
        miniScreenShakingTime.restart();
    }

    if (player.isDamaged()) {
        screenShaking = true;
        screenShackingTime.restart();
    }

    if (screenShackingTime.getElapsedTime().asMilliseconds() >= 200) {
        screenShaking = false;
    }

    if (miniScreenShakingTime.getElapsedTime().asMilliseconds() >= 150) {
        miniScreenShaking = false;
    }

    if (gameState == PAUSED) {
        screenShaking = false;
    }

    if (screenShaking) {
        sf::View view(sf::FloatRect(rand() % 10, rand() % 10, window->getSize().x + rand() % 10,
                                    window->getSize().y + rand() % 10));

        window->setView(view);
    }
    else if (miniScreenShaking) {
        sf::View view(sf::FloatRect(rand() % 5, rand() % 5, window->getSize().x + rand() % 5,
                                    window->getSize().y + rand() % 5));

        window->setView(view);
    }
    else {
        window->setView(sf::View(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y)));
    }

}

void Game::renderGame() {
    window->draw(background);
    window->draw(entities);
    window->draw(player);
    window->draw(score);
}

void Game::menuHandler() {
    if (gameState == INMENU) {
        menu.setState(Status::INMAINMENU);
        if (clickSleep.getElapsedTime().asMilliseconds() > 500) {
            if (menu.isPressed(Buttons::PLAY)) {
                restart();
                music.start();
                gameState = INGAME;
                clickSleep.restart();
            }
            if (menu.isPressed(Buttons::EXIT)) {
                window->close();
            }
        }
    }
    else if (gameState == GAMEOVER) {
        menu.setState(Status::INRETRYMENU);
        if (clickSleep.getElapsedTime().asMilliseconds() > 500) {
            if (menu.isPressed(Buttons::RETRY)) {
                restart();
                gameState = INGAME;
                clickSleep.restart();
            }
            if (menu.isPressed(Buttons::MENU)) {
                gameState = INMENU;
                clickSleep.restart();
            }
        }
    }
    else if (gameState == PAUSED) {
        menu.setState(Status::INPAUSEMENU);
        if (clickSleep.getElapsedTime().asMilliseconds() > 500) {
            if (menu.isPressed(Buttons::RESUME)) {
                gameState = INGAME;
                music.resume();
                clickSleep.restart();
            }
            if (menu.isPressed(Buttons::MENU)) {
                gameState = INMENU;
                music.resume();
                clickSleep.restart();
            }
        }
    }
    else if (gameState == INGAME) {
        menu.setState(Status::NONE);
    }
}

void Game::updateMenu() {
    mouse.update(sf::Mouse::getPosition(*window));
    menu.updateMousePosition(mouse.getGlobalBounds());
    menu.update();
}

void Game::renderMenu() {
    window->draw(menu);
    window->draw(mouse);
    window->draw(highscore);
}

void Game::inputProcess() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();

        if (event.type == sf::Event::LostFocus) {
            if (gameState == INGAME) {
                gameState = PAUSED;
                music.pause();
            }
        }

        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Escape) {
                if (gameState == INMENU) {
                    window->close();
                }

                gameState = PAUSED;
                music.pause();
            }
            if (event.key.code == sf::Keyboard::P) {
                music.next();
            }
        }
    }
    frameTime = frameClock.restart();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
        player.setHp(0);
}

void Game::loop() {
    while (window->isOpen()) {
        inputProcess();

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
        if (gameState == PAUSED) {
            menuHandler();
            updateGame();
            updateMenu();
            renderGame();
            renderMenu();
        }

        window->display();
    }
}

void Game::restart() {
    entities.clear();
    player.reset();
    score.reset();
    music.restart();
}

void Game::loadTextures() {
    std::vector<string> texList = {"../res/textures/play.png", "../res/textures/play-hover.png",
                                   "../res/textures/exit.png", "../res/textures/exit-hover.png",
                                   "../res/textures/resume.png", "../res/textures/resume-hover.png",
                                   "../res/textures/retry.png", "../res/textures/retry-hover.png",
                                   "../res/textures/menu.png", "../res/textures/menu-hover.png",
                                   "../res/textures/heart.png", "../res/textures/background.png",
                                   "../res/textures/background1.png", "../res/textures/player.png",
                                   "../res/textures/player-core.png", "../res/textures/shield.png",
                                   "../res/textures/bullet11.png", "../res/textures/bullet12.png",
                                   "../res/textures/bullet13.png", "../res/textures/bullet14.png",
                                   "../res/textures/bullet15.png", "../res/textures/bullet16.png",
                                   "../res/textures/bullet21.png", "../res/textures/bullet22.png",
                                   "../res/textures/bullet23.png", "../res/textures/bullet24.png",
                                   "../res/textures/bullet25.png", "../res/textures/bullet26.png",
                                   "../res/textures/enemy1.png", "../res/textures/enemy2.png",
                                   "../res/textures/enemy3.png", "../res/textures/enemy4.png",
                                   "../res/textures/enemy5.png", "../res/textures/enemy6.png",
                                   "../res/textures/explosion11.png", "../res/textures/explosion12.png",
                                   "../res/textures/explosion13.png", "../res/textures/explosion21.png",
                                   "../res/textures/explosion22.png", "../res/textures/explosion23.png",
                                   "../res/textures/explosion31.png", "../res/textures/explosion32.png",
                                   "../res/textures/explosion33.png", "../res/textures/explosion41.png",
                                   "../res/textures/explosion42.png", "../res/textures/explosion43.png",
                                   "../res/textures/explosion51.png", "../res/textures/explosion52.png",
                                   "../res/textures/explosion53.png", "../res/textures/explosion61.png",
                                   "../res/textures/explosion62.png", "../res/textures/explosion63.png",
                                   "../res/textures/cursor.png"};

    for (int i = 0; i < texList.size(); i++) {
        texture.getTexture(texList[i]);
    }
}

void Game::start() {
    loop();
}

int main() {
    Game game;

    game.start();

    return 0;
}
