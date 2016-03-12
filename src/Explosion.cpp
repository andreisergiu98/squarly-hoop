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

#include "Explosion.h"

Explosion::Explosion(sf::Vector2f position, sf::Vector2f size, sf::Texture &texture) {
    form.setPosition(position);
    form.setSize(sf::Vector2f(size.x + 5, size.y + 5));
    form.setTexture(&texture);
    form.setOrigin(size.x / 2, size.y / 2);

    float angle = rand() % 360 + 0;
    form.rotate(angle);

    opacity = 255;
}

void Explosion::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(form);
}

bool Explosion::destroy() {
    return clock.getElapsedTime().asMilliseconds() > 2550;
}

void Explosion::update() {
    if (fadeOut.getElapsedTime().asMilliseconds() >= 0.5) {
        if(opacity)
            opacity--;
        fadeOut.restart();
    }


    form.setFillColor(sf::Color(255, 255, 255, opacity));
}
