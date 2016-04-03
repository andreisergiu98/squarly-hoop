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

#ifndef SFMLGAME_MENU_H
#define SFMLGAME_MENU_H

#include "Button.h"
#include "../TextureManager.h"
#include "../sound/Sound.h"
#include <SFML/Graphics.hpp>

enum Buttons {
    PLAY, EXIT, RETRY, MENU, RESUME
};

enum Status {
    INMAINMENU, INRETRYMENU, INPAUSEMENU, NONE
};

class Menu : public sf::Drawable {
public:
    Menu();

    Menu(sf::FloatRect windowBounds, TextureManager *textureManager);

    void updateMousePosition(sf::FloatRect mouse);

    void update();

    bool isPressed(Buttons);

    void setState(Status status);

private:
    void playBeep();

    Button play;
    Button exit;
    Button retry;
    Button resume;
    Button menu;

    TextureManager *texture;

    sf::RectangleShape background;
    Status status;

    Sound *beep;

    enum Beeped {
        PLAY, EXIT, RETRY, MENU, RESUME, NONE
    };

    Beeped beeped;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};


#endif //SFMLGAME_MENU_H
