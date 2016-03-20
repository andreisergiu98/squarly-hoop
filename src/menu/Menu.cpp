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
    play = Button(sf::Vector2f(400, 250), sf::Vector2f(200, 80), texture.getTexture("../res/textures/play.png"),
                  texture.getTexture("../res/textures/play-hover.png"));
    exit = Button(sf::Vector2f(400, 450), sf::Vector2f(200, 80), texture.getTexture("../res/textures/exit.png"),
                  texture.getTexture("../res/textures/exit-hover.png"));
    retry = Button(sf::Vector2f(400, 250), sf::Vector2f(200, 80), texture.getTexture("../res/textures/retry.png"),
                   texture.getTexture("../res/textures/retry-hover.png"));
    menu = Button(sf::Vector2f(400, 450), sf::Vector2f(200, 80), texture.getTexture("../res/textures/menu.png"),
                  texture.getTexture("../res/textures/menu-hover.png"));

    status = INMAINMENU;

    background.setSize(sf::Vector2f(1000, 900));
    background.setPosition(0, 0);
    background.setFillColor(sf::Color(0, 0, 0, 150));
}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(background);

    if (status == INMAINMENU) {
        target.draw(play);
        target.draw(exit);
    }
    if (status == INRETRYMENU) {
        target.draw(retry);
        target.draw(menu);
    }

}

void Menu::updateMousePosition(sf::Vector2i i) {
    play.updateMouse(i);
    exit.updateMouse(i);
    retry.updateMouse(i);
    menu.updateMouse(i);
}

void Menu::update() {
    play.update();
    exit.update();
    retry.update();
    menu.update();
}

bool Menu::isPressed(Buttons buttons) {
    if (buttons == PLAY) {
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

void Menu::setState(Status status) {
    this->status = status;
}
