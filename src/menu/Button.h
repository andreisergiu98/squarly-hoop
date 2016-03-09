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

#ifndef SFMLGAME_BUTTON_H
#define SFMLGAME_BUTTON_H

#include <SFML/Graphics.hpp>

class Button : public sf::Drawable {
public:
    Button(){}
    Button(sf::Vector2f position, sf::Vector2f size, sf::Texture &texNormal, sf::Texture &texMouseOver);

    void update();
    void updateMouse(sf::Vector2i);
    bool isPressed();

private:
    sf::RectangleShape form;
    sf::FloatRect mouse;
    std::unique_ptr<sf::Texture> texNormal;
    std::unique_ptr<sf::Texture> texMouseOver;

    enum Mouse{
        MOUSEOVER, NORMAL, ISPRESSED};
    Mouse status;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};


#endif //SFMLGAME_BUTTON_H
