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

#include "ShootingPaterns.h"

std::vector<Bullet> getBulletsPatern(ShootingPatern patern, sf::Vector2f position, sf::Vector2i destination,
                                     float speed, sf::Texture &texture, int id) {
    if (patern == SPREAD) {
        return spread(position, destination, speed, texture, id);
    }
    if (patern == SPREAD2) {
        return spread(position, destination, speed, texture, id);
    }
    if (patern == SPIRAL) {
        return spread(position, destination, speed, texture, id);
    }
    if (patern == STRAIGHT) {
        return spread(position, destination, speed, texture, id);
    }
}

std::vector<Bullet> spread(sf::Vector2f position, sf::Vector2i destination, float speed, sf::Texture &texture, int id) {
    std::vector<Bullet> bullets;

    Bullet bullet1(position, sf::Vector2i(destination.x - 200, destination.y), speed, texture, id);
    Bullet bullet2(position, sf::Vector2i(destination.x, destination.y), speed, texture, id);
    Bullet bullet3(position, sf::Vector2i(destination.x + 200, destination.y), speed, texture, id);

    bullets.push_back(bullet1);
    bullets.push_back(bullet2);
    bullets.push_back(bullet3);

    return bullets;
}

std::vector<Bullet> spread2(sf::Vector2f position, sf::Vector2i destination, float speed, sf::Texture &texture,
                            int id) {

}

std::vector<Bullet> spiral(sf::Vector2f position, sf::Vector2i destination, float speed, sf::Texture &texture, int id) {

}

std::vector<Bullet> straight(sf::Vector2f position, sf::Vector2i destination, float speed, sf::Texture &texture,
                             int id) {

}
