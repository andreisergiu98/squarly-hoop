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

#include "Menu.h"

Menu::Menu() {
    play = Button(sf::Vector2f(400, 200), sf::Vector2f(200, 80), texture.getTexture("../res/Textures/play.png"),
                  texture.getTexture("../res/Textures/play-hover.png"));
    highscore = Button(sf::Vector2f(400, 350), sf::Vector2f(200, 80), texture.getTexture("../res/Textures/play.png"),
                       texture.getTexture("../res/Textures/play-hover.png"));
    exit = Button(sf::Vector2f(400, 500), sf::Vector2f(200, 80), texture.getTexture("../res/Textures/exit.png"),
                  texture.getTexture("../res/Textures/exit-hover.png"));
    retry = Button(sf::Vector2f(400, 600), sf::Vector2f(60, 20), texture.getTexture("../res/Textures/retry.png"),
                   texture.getTexture("../res/Textures/retry-hover.png"));
    menu = Button(sf::Vector2f(150, 280), sf::Vector2f(60, 20), texture.getTexture("../res/Textures/menu.png"),
                  texture.getTexture("../res/Textures/menu-hover.png"));

    status = INMENU;
}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (status == INMENU) {
        target.draw(play);
        target.draw(highscore);
        target.draw(exit);
    }
    if (status == GAMEOVER) {
        target.draw(retry);
        target.draw(menu);
    }
}

void Menu::updateMousePosition(sf::Vector2i i) {
    play.updateMouse(i);
    highscore.updateMouse(i);
    exit.updateMouse(i);
    retry.updateMouse(i);
    menu.updateMouse(i);
}

void Menu::update() {
    play.update();
    highscore.update();
    exit.update();
    retry.update();
    menu.update();
}

bool Menu::isPressed(Buttons buttons) {
    if (buttons == PLAY) {
        return play.isPressed();
    }
    if (buttons == OPTIONS) {
        return play.isPressed();
    }
    if (buttons == EXIT) {
        return exit.isPressed();
    }
    if (buttons == RETRY) {
        return retry.isPressed();
    }
    if (buttons == MENU) {
        return menu.isPressed();
    }
}
