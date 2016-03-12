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
                                     float speed, sf::Texture &texture, int color) {
    if (patern == SPREAD) {
        return spread(position, destination, speed, texture, color);
    }
    if (patern == SPREAD2) {
        return spread2(position, destination, speed, texture, color);
    }
    if (patern == CIRCLE) {
        return circle(position, destination, speed, texture, color);
    }
    if (patern == STRAIGHT) {
        return straight(position, destination, speed, texture, color);
    }
}

std::vector<Bullet> spread(sf::Vector2f position, sf::Vector2f destination, float speed, sf::Texture &texture,
                           int color) {
    std::vector<Bullet> bullets;

    sf::Transform rotation;
    sf::Transform inverseRotation;

    Bullet bullet = Bullet(position, destination, speed, texture, color);

    bullets.push_back(bullet);

    for (int i = 0; i <= 2; i++) {
        rotation.rotate(6, position.x, position.y);
        inverseRotation.rotate(-6, position.x, position.y);

        Bullet bullet1 = Bullet(position, rotation.transformPoint(destination), speed, texture, color);

        Bullet bullet2 = Bullet(position, inverseRotation.transformPoint(destination), speed, texture, color);

        bullets.push_back(bullet1);
        bullets.push_back(bullet2);
    }

    return bullets;
}

std::vector<Bullet> spread2(sf::Vector2f position, sf::Vector2f destination, float speed, sf::Texture &texture,
                            int color) {
    std::vector<Bullet> bullets;

    sf::Transform rotation;
    sf::Transform inverseRotation;

    Bullet bullet = Bullet(position, destination, speed, texture, color);

    bullets.push_back(bullet);

    for (int i = 0; i <= 5; i++) {
        rotation.rotate(2, position.x, position.y);
        inverseRotation.rotate(-2, position.x, position.y);

        Bullet bullet1 = Bullet(position, rotation.transformPoint(destination), speed, texture, color);

        Bullet bullet2 = Bullet(position, inverseRotation.transformPoint(destination), speed, texture, color);

        bullets.push_back(bullet1);
        bullets.push_back(bullet2);
    }

    return bullets;
}

std::vector<Bullet> circle(sf::Vector2f position, sf::Vector2f destination, float speed, sf::Texture &texture,
                           int color) {
    std::vector<Bullet> bullets;

    for (int i = 0; i <= 360; i += 10) {
        sf::Vector2f dest(position.x + (float) cos(i * pi / 180), position.y + (float) sin(i * pi / 180));
        Bullet bullet(position, dest, speed, texture, color);
        bullets.push_back(bullet);
    }

    return bullets;
}

std::vector<Bullet> straight(sf::Vector2f position, sf::Vector2f destination, float speed, sf::Texture &texture,
                             int color) {
    std::vector<Bullet> bullets;
    Bullet bullet1(sf::Vector2f(position.x - 10, position.y), sf::Vector2f(destination.x - 10, destination.y), speed,
                   texture, color);
    Bullet bullet2(sf::Vector2f(position.x + 10, position.y), sf::Vector2f(destination.x + 10, destination.y), speed,
                   texture, color);

    bullets.push_back(bullet1);
    bullets.push_back(bullet2);

    return bullets;
}
