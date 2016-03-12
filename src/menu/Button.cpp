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

#include "Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Texture &texNormal, sf::Texture &texMouseOver) {
    form.setPosition(position);
    form.setSize(size);
    form.setTexture(&texNormal);
    mouse.width = 5;
    mouse.height = 5;

    this->texNormal = &texNormal;
    this->texMouseOver = &texMouseOver;
    status = NORMAL;
}

void Button::updateMouse(sf::Vector2i mousePosition) {
    mouse.top = mousePosition.y;
    mouse.left = mousePosition.x;
}

void Button::update() {
    if (status == NORMAL and form.getGlobalBounds().intersects(mouse)) {
        form.setTexture(texMouseOver);
        status = MOUSEOVER;
    }
    if (status == MOUSEOVER and !form.getGlobalBounds().intersects(mouse)) {
        form.setTexture(texNormal);
        status = NORMAL;
    }
}

bool Button::isPressed() {
    return status == MOUSEOVER and sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(form);
}
