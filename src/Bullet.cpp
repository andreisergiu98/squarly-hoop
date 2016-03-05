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

#include "Bullet.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2i destination, float speed, sf::Texture &texture, int id) {
    form.setPosition(position);
    form.setSize(sf::Vector2f(11, 11));
    form.setTexture(&texture);

    float dist = (float) sqrt((destination.x - position.x) * (destination.x - position.x) +
                              (destination.y - position.y) * (destination.y - position.y));

    velocity.x = (destination.x - position.x) / dist;
    velocity.y = (destination.y - position.y) / dist;

    velocity *= speed;

    form.setOrigin(5.5, 5.5);

    this->id = id;
}

void Bullet::update(sf::Time frameTime) {
    this->frameTime = frameTime;
}

void Bullet::process() {
    form.move(velocity * frameTime.asSeconds());
    form.rotate(60);
}

sf::FloatRect Bullet::getGlobalBounds() {
    sf::FloatRect boundingBox = form.getGlobalBounds();
    boundingBox.top += 4;
    boundingBox.left += 4;
    boundingBox.height -= 8;
    boundingBox.width -= 8;

    return boundingBox;
}

void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(form);
}

int Bullet::getId() {
    return id;
}

sf::Vector2f Bullet::getPosition() {
    return form.getPosition();
}

sf::Vector2f Bullet::getSize() {
    return form.getSize();
}
