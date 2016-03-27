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

#include "Mouse.h"

Mouse::Mouse(sf::Texture *texture) {
    form.setSize(sf::Vector2f(15, 15));
    form.setTexture(texture);
}

void Mouse::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(form);
}

void Mouse::update(sf::Vector2i pos) {
    form.setPosition(sf::Vector2f(pos.x, pos.y));
}

sf::FloatRect Mouse::getGlobalBounds() {
    return form.getGlobalBounds();
}







