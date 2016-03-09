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
#include "debug/Debug.h"

#define pi 3.14159265f

std::vector<Bullet> getBulletsPatern(ShootingPatern patern, sf::Vector2f position, sf::Vector2f destination,
                                     float speed, sf::Texture &texture, int id) {
    if (patern == SPREAD) {
        return spread(position, destination, speed, texture, id);
    }
    if (patern == SPREAD2) {
        return spread2(position, destination, speed, texture, id);
    }
    if (patern == CIRCLE) {
        return circle(position, destination, speed, texture, id);
    }
    if (patern == STRAIGHT) {
        return straight(position, destination, speed, texture, id);
    }
}

std::vector<Bullet> spread(sf::Vector2f position, sf::Vector2f destination, float speed, sf::Texture &texture, int id) {
    std::vector<Bullet> bullets;

    Bullet bullet1;
    Bullet bullet3;
    if (destination.y - position.y < 0) {
        bullet1 = Bullet(position, sf::Vector2f(
                                 (float) (cos(30 * pi / 180) * destination.x + sin(30 * pi / 180) * destination.y),
                                 (float) (-sin(30 * pi / 180) * destination.x + cos(30 * pi / 180) * destination.y)),
                         speed, texture,
                         id);
        bullet3 = Bullet(position, sf::Vector2f(
                                 (float) (cos(-30 * pi / 180) * destination.x + sin(-30 * pi / 180) * destination.y),
                                 (float) (-sin(-30 * pi / 180) * destination.x + cos(-30 * pi / 180) * destination.y)),
                         speed, texture,
                         id);
    }
    else {
        bullet1 = Bullet(position, sf::Vector2f(
                                 (float) (cos(30 * pi / 180) * destination.x - sin(30 * pi / 180) * destination.y),
                                 (float) (sin(30 * pi / 180) * destination.x + cos(30 * pi / 180) * destination.y)),
                         speed, texture,
                         id);
        bullet3 = Bullet(position, sf::Vector2f(
                                 (float) (cos(-30 * pi / 180) * destination.x - sin(-30 * pi / 180) * destination.y),
                                 (float) (sin(-30 * pi / 180) * destination.x + cos(-30 * pi / 180) * destination.y)),
                         speed, texture,
                         id);
    }
    Bullet bullet2(position, destination, speed, texture, id);

    bullets.push_back(bullet1);
    bullets.push_back(bullet2);
    bullets.push_back(bullet3);

    return bullets;
}

std::vector<Bullet> spread2(sf::Vector2f position, sf::Vector2f destination, float speed, sf::Texture &texture,
                            int id) {
    std::vector<Bullet> bullets;


    Bullet bullet1(position,
                   sf::Vector2f(position.x - (float) cos(90 * pi / 180), position.y - (float) sin(90 * pi / 180)),
                   speed, texture, id);
    Bullet bullet2(position,
                   sf::Vector2f(position.x - (float) cos(105 * pi / 180), position.y - (float) sin(105 * pi / 180)),
                   speed, texture, id);
    Bullet bullet3(position,
                   sf::Vector2f(position.x - (float) cos(75 * pi / 180), position.y - (float) sin(75 * pi / 180)),
                   speed, texture, id);
    Bullet bullet4(position,
                   sf::Vector2f(position.x - (float) cos(120 * pi / 180), position.y - (float) sin(120 * pi / 180)),
                   speed, texture, id);
    Bullet bullet5(position,
                   sf::Vector2f(position.x - (float) cos(60 * pi / 180), position.y - (float) sin(60 * pi / 180)),
                   speed, texture, id);

    bullets.push_back(bullet1);
    bullets.push_back(bullet2);
    bullets.push_back(bullet3);
    bullets.push_back(bullet4);
    bullets.push_back(bullet5);

    return bullets;
}

std::vector<Bullet> circle(sf::Vector2f position, sf::Vector2f destination, float speed, sf::Texture &texture, int id) {
    std::vector<Bullet> bullets;

    for (int i = 0; i <= 360; i += 10) {
        sf::Vector2f dest(position.x + (float) cos(i * pi / 180), position.y + (float) sin(i * pi / 180));
        Bullet bullet(position, dest, speed, texture, id);
        bullets.push_back(bullet);
    }

    return bullets;
}

std::vector<Bullet> straight(sf::Vector2f position, sf::Vector2f destination, float speed, sf::Texture &texture,
                             int id) {
    std::vector<Bullet> bullets;
    Bullet bullet1(sf::Vector2f(position.x - 10, position.y), sf::Vector2f(destination.x - 10, destination.y), speed,
                   texture, id);
    Bullet bullet2(sf::Vector2f(position.x + 10, position.y), sf::Vector2f(destination.x + 10, destination.y), speed,
                   texture, id);

    bullets.push_back(bullet1);
    bullets.push_back(bullet2);

    return bullets;
}
