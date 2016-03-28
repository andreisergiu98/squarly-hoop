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

#ifndef SFMLGAME_BACKGROUND_H
#define SFMLGAME_BACKGROUND_H

#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class Background : public sf::Drawable {

public:
    Background() { }

    Background(sf::FloatRect windowBounds, sf::Vector2f size, sf::Texture *textureFirst, sf::Texture *textureSecond);

    void process();

    void update(sf::Time frameTime);

    void colorUpdate();

private:
    sf::RectangleShape first;
    sf::RectangleShape second;

    sf::FloatRect bounds;

    sf::Vector2f velocity;

    sf::Time frameTime;

    float length;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif //SFMLGAME_BACKGROUND_H
