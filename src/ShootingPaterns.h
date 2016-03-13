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

namespace EnemyPatterns {
    enum Pattern {
        SPREAD, SPREADMAX, CIRCLE, SIMPLE
    };

    std::vector<Bullet> getBullets(Pattern pattern, sf::Vector2f position, sf::Vector2f destination,
                                   float speed, sf::Texture &texture, int color);

    std::vector<Bullet> spread(sf::Vector2f position, sf::Vector2f destination, float speed, sf::Texture &texture,
                               int color);

    std::vector<Bullet> spreadmax(sf::Vector2f position, sf::Vector2f destination, float speed, sf::Texture &texture,
                                  int color);

    std::vector<Bullet> circle(sf::Vector2f position, sf::Vector2f destination, float speed, sf::Texture &texture,
                               int color);

    std::vector<Bullet> simple(sf::Vector2f position, sf::Vector2f destination, float speed, sf::Texture &texture,
                               int color);

}

namespace PlayerPatterns{
    enum Pattern{
        SIMPLE, SPREAD, SPREADMAX
    };

    std::vector<Bullet> getBullets(Pattern pattern, sf::Vector2f position, float speed, sf::Texture &texture, int color);

    std::vector<Bullet> simple(sf::Vector2f position, float speed, sf::Texture &texture, int color);

    std::vector<Bullet> spread(sf::Vector2f position, float speed, sf::Texture &texture, int color);

    std::vector<Bullet> spreadmax(sf::Vector2f position, float speed, sf::Texture &texture, int color);
}


#endif //SFMLGAME_SHOOTINGPATERNS_H
