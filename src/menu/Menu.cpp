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
}

Menu::Menu(sf::FloatRect windowBounds, TextureManager *textureManager) {
    texture = textureManager;

    play = Button(sf::Vector2f(windowBounds.width / 2.f - 100, (windowBounds.height + 100) / 4.f),
                  sf::Vector2f(200, 80),
                  texture->getTexture("../res/textures/play.png"),
                  texture->getTexture("../res/textures/play-hover.png"));
    exit = Button(sf::Vector2f(windowBounds.width / 2.f - 100, (windowBounds.height + 100) / 2.f),
                  sf::Vector2f(200, 80),
                  texture->getTexture("../res/textures/exit.png"),
                  texture->getTexture("../res/textures/exit-hover.png"));
    retry = Button(sf::Vector2f(windowBounds.width / 2.f - 100, (windowBounds.height + 100) / 4.f),
                   sf::Vector2f(200, 80),
                   texture->getTexture("../res/textures/retry.png"),
                   texture->getTexture("../res/textures/retry-hover.png"));
    resume = Button(sf::Vector2f(windowBounds.width / 2.f - 105, (windowBounds.height + 100) / 4.f),
                    sf::Vector2f(220, 80),
                    texture->getTexture("../res/textures/resume.png"),
                    texture->getTexture("../res/textures/resume-hover.png"));
    menu = Button(sf::Vector2f(windowBounds.width / 2.f - 100, (windowBounds.height + 100) / 2.f),
                  sf::Vector2f(200, 80),
                  texture->getTexture("../res/textures/menu.png"),
                  texture->getTexture("../res/textures/menu-hover.png"));

    status = INMAINMENU;

    background.setSize(sf::Vector2f(windowBounds.width, windowBounds.height));
    background.setPosition(0, 0);
    background.setFillColor(sf::Color(0, 0, 0, 150));

    beep = new Sound();

    beep->loadSound("../res/sounds/select.wav");
    beeped = NONE;
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
    if (status == INPAUSEMENU) {
        target.draw(resume);
        target.draw(menu);
    }
}

void Menu::updateMousePosition(sf::FloatRect mouse) {
    play.updateMouse(mouse);
    exit.updateMouse(mouse);
    retry.updateMouse(mouse);
    resume.updateMouse(mouse);
    menu.updateMouse(mouse);
}

void Menu::update() {
    play.update();
    exit.update();
    retry.update();
    resume.update();
    menu.update();
    playBeep();
}

bool Menu::isPressed(Buttons button) {
    if (button == Buttons::PLAY) {
        return play.isPressed();
    }
    else if (button == Buttons::EXIT) {
        return exit.isPressed();
    }
    else if (button == Buttons::RETRY) {
        return retry.isPressed();
    }
    else if (button == Buttons::MENU) {
        return menu.isPressed();
    }
    else if (button == Buttons::RESUME) {
        return resume.isPressed();
    }

    return false;
}

void Menu::setState(Status status) {
    this->status = status;
}

void Menu::playBeep() {
    if (status != Status::NONE) {
        if (play.getStatus() == ButtonStatus::MOUSEOVER) {
            if (beeped != Beeped::PLAY) {
                beep->play();
            }
            beeped = Beeped::PLAY;
        }
        else if (exit.getStatus() == ButtonStatus::MOUSEOVER) {
            if (beeped != Beeped::EXIT) {
                beep->play();
            }
            beeped = Beeped::EXIT;
        }
        else if (resume.getStatus() == ButtonStatus::MOUSEOVER) {
            if (beeped != Beeped::RESUME) {
                beep->play();
            }
            beeped = Beeped::RESUME;
        }
        else if (retry.getStatus() == ButtonStatus::MOUSEOVER) {
            if (beeped != Beeped::RETRY) {
                beep->play();
            }
            beeped = Beeped::RETRY;
        }
        else if (menu.getStatus() == ButtonStatus::MOUSEOVER) {
            if (beeped != Beeped::MENU) {
                beep->play();
            }
            beeped = Beeped::MENU;
        }
        else {
            beeped = Beeped::NONE;
        }
    }
}





