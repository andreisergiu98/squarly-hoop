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

#ifndef SFMLGAME_BULLET_H
#define SFMLGAME_BULLET_H


#include <SFML/Graphics.hpp>

class Bullet : public sf::Drawable {
public:
    Bullet() { }

    Bullet(sf::Vector2f position, sf::Vector2i destination, float speed, sf::Texture &texture, int id);

    void update(sf::Time frameTime);

    void process();

    sf::Vector2f getPosition();

    sf::Vector2f getSize();

    int getId();

    sf::FloatRect getGlobalBounds();

private:
    sf::RectangleShape form;

    sf::Vector2f velocity;

    sf::Time frameTime;

    int id;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};


#endif //SFMLGAME_BULLET_H
