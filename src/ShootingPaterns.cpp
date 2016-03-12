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

#include <SFML/System/Vector2.hpp>
#include "ShootingPaterns.h"

namespace EnemyPatterns {

    std::vector<Bullet> getBullets(Pattern pattern, sf::Vector2f position, sf::Vector2f destination,
                                   float speed, sf::Texture &texture, int color) {
        if (pattern == SPREAD) {
            return spread(position, destination, speed, texture, color);
        }
        if (pattern == SPREADMAX) {
            return spread2(position, destination, speed, texture, color);
        }
        if (pattern == CIRCLE) {
            return circle(position, destination, speed, texture, color);
        }
        if (pattern == STRAIGHT) {
            return straight(position, destination, speed, texture, color);
        }
        return std::vector<Bullet>();
    }

    std::vector<Bullet> spread(sf::Vector2f position, sf::Vector2f destination, float speed, sf::Texture &texture,
                               int color) {
        std::vector<Bullet> bullets;

        sf::Transform rotation;
        sf::Transform inverseRotation;

        Bullet bullet = Bullet(position, destination, speed, texture, color);

        bullets.push_back(bullet);

        for (int i = 0; i <= 2; i++) {
            rotation.rotate(6, position);
            inverseRotation.rotate(-6, position);

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
            rotation.rotate(2, position);
            inverseRotation.rotate(-2, position);

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
        sf::Transform rotation;

        Bullet bullet = Bullet(position, destination, speed, texture, color);
        bullets.push_back(bullet);

        for (int i = 0; i <= 360; i += 10) {
            //sf::Vector2f dest(position.x + (float) cos(i * pi / 180), position.y + (float) sin(i * pi / 180));
            rotation.rotate(10, position);
            bullet = Bullet(position, rotation.transformPoint(destination), speed, texture, color);
            bullets.push_back(bullet);
        }

        return bullets;
    }

    std::vector<Bullet> straight(sf::Vector2f position, sf::Vector2f destination, float speed, sf::Texture &texture,
                                 int color) {
        std::vector<Bullet> bullets;
        Bullet bullet1(sf::Vector2f(position.x - 10, position.y), sf::Vector2f(destination.x - 10, destination.y),
                       speed,
                       texture, color);
        Bullet bullet2(sf::Vector2f(position.x + 10, position.y), sf::Vector2f(destination.x + 10, destination.y),
                       speed,
                       texture, color);

        bullets.push_back(bullet1);
        bullets.push_back(bullet2);

        return bullets;
    }
}

namespace PlayerPatterns {
    std::vector<Bullet> getBullets(Pattern pattern, sf::Vector2f position, float speed, sf::Texture &texture,
                                   int color) {
        if (pattern == SIMPLE) {
            return simple(position, speed, texture, color);
        }
        if (pattern == SPREAD) {
            return spread(position, speed, texture, color);
        }
        if (pattern == SPREADMAX) {
            return spreadmax(position, speed, texture, color);
        }
        return std::vector<Bullet>();
    }

    std::vector<Bullet> simple(sf::Vector2f position, float speed, sf::Texture &texture, int color) {
        std::vector<Bullet> bullets;

        Bullet bullet = Bullet(sf::Vector2f(position.x - 7, position.y), sf::Vector2f(position.x - 7, position.y - 5),
                               speed, texture, color);
        bullets.push_back(bullet);

        bullet = Bullet(sf::Vector2f(position.x + 7, position.y), sf::Vector2f(position.x + 7, position.y - 5), speed,
                        texture, color);
        bullets.push_back(bullet);

        return bullets;
    }

    std::vector<Bullet> spread(sf::Vector2f position, float speed, sf::Texture &texture, int color) {
        std::vector<Bullet> bullets(simple(position, speed, texture, color));

        sf::Transform rotation;
        sf::Transform inverseRotation;
        sf::Vector2f target = sf::Vector2f(position.x, position.y - 100);

        rotation.rotate(15, position);
        inverseRotation.rotate(-15, position);

        Bullet bullet1 = Bullet(position, rotation.transformPoint(target), speed, texture, color);

        Bullet bullet2 = Bullet(position, inverseRotation.transformPoint(target), speed, texture, color);

        bullets.push_back(bullet1);
        bullets.push_back(bullet2);

        return bullets;
    }

    std::vector<Bullet> spreadmax(sf::Vector2f position, float speed, sf::Texture &texture, int color) {
        std::vector<Bullet> bullets(simple(position, speed, texture, color));

        sf::Transform rotation;
        sf::Transform inverseRotation;
        sf::Vector2f target = sf::Vector2f(position.x, position.y - 100);

        for (int i = 0; i <= 5; i += 5) {
            rotation.rotate(15 + i, position);
            inverseRotation.rotate(-15 - i, position);

            Bullet bullet1 = Bullet(position, rotation.transformPoint(target), speed, texture, color);

            Bullet bullet2 = Bullet(position, inverseRotation.transformPoint(target), speed, texture, color);

            bullets.push_back(bullet1);
            bullets.push_back(bullet2);
        }

        return bullets;
    }
}