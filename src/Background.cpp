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

#include "Background.h"

Background::Background(sf::FloatRect windowBounds, sf::Vector2f size, sf::Texture *textureFirst,
                       sf::Texture *textureSecond) {
    length = size.y;

    bounds = windowBounds;
    first.setPosition(0, 0);
    first.setSize(size);
    first.setTexture(textureFirst);
    second.setPosition(0, -length);
    second.setSize(size);
    second.setTexture(textureSecond);

    velocity = sf::Vector2f(0, 200);
}

void Background::process() {
    first.move(velocity * frameTime.asSeconds());
    second.move(velocity * frameTime.asSeconds());

    if (!first.getGlobalBounds().intersects(bounds)) {
        first.setPosition(sf::Vector2f(0, second.getPosition().y - length));
    }
    if (!second.getGlobalBounds().intersects(bounds)) {
        second.setPosition(sf::Vector2f(0, first.getPosition().y - length));
    }
}

void Background::update(sf::Time frameTime) {
    this->frameTime = frameTime;
}

void Background::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(first);
    target.draw(second);
}

void Background::colorUpdate() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 255);

    int r = distribution(gen);
    int g = distribution(gen);
    int b = distribution(gen);

    //sf::Color color(16, 218, 116);
    sf::Color color(r, g, b);

    first.setFillColor(color);
    second.setFillColor(color);

    Debug::print(r, g, b);
}







