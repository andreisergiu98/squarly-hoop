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
#include "Utilities.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f destination, float speed, sf::Texture &texture, int color) {
    form.setPosition(position);
    form.setSize(sf::Vector2f(11, 11));
    form.setTexture(&texture);

    velocity = utilities::calcVelocity(position, destination);

    velocity *= speed;

    form.setOrigin(sf::Vector2f(form.getSize().x / 2.f, form.getSize().y / 2.f));

    this->color = color;
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

int Bullet::getColor() {
    return color;
}

sf::Vector2f Bullet::getPosition() {
    return form.getPosition();
}

sf::Vector2f Bullet::getSize() {
    return form.getSize();
}

sf::Color Bullet::getColorCode() {
    if (color == 1) {
        return sf::Color::Blue;
    }
    if (color == 2) {
        return sf::Color::Cyan;
    }
    if (color == 3) {
        return sf::Color::Green;
    }
    if (color == 4) {
        return sf::Color::Red;
    }
    if (color == 5) {
        return sf::Color::Magenta;
    }
    if (color == 6) {
        return sf::Color::Yellow;
    }
}



