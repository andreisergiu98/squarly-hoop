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

#ifndef SFMLGAME_SHOOTINGPATERNS_H
#define SFMLGAME_SHOOTINGPATERNS_H

#include "Bullet.h"

enum ShootingPatern {
    SPREAD, SPREAD2, SPIRAL, STRAIGHT
};

std::vector<Bullet> getBulletsPatern(ShootingPatern patern, sf::Vector2f position, sf::Vector2i destination,
                                     float speed, sf::Texture &texture, int id);

std::vector<Bullet> spread(sf::Vector2f position, sf::Vector2i destination, float speed, sf::Texture &texture, int id);

std::vector<Bullet> spread2(sf::Vector2f position, sf::Vector2i destination, float speed, sf::Texture &texture, int id);

std::vector<Bullet> spiral(sf::Vector2f position, sf::Vector2i destination, float speed, sf::Texture &texture, int id);

std::vector<Bullet> straight(sf::Vector2f position, sf::Vector2i destination, float speed, sf::Texture &texture,
                             int id);

#endif //SFMLGAME_SHOOTINGPATERNS_H
