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

#ifndef SFMLGAME_PLAYER_H
#define SFMLGAME_PLAYER_H

#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Bullet.h"
#include "ShootingPaterns.h"

class Player : public sf::Drawable {
public:
    Player() { }

    Player(sf::FloatRect windowBounds);

    void update(sf::Time frameTime);

    void process();

    sf::Vector2f getPosition();

    int getHp();

    void reset();

    void setHp(int);

    sf::FloatRect getGlobalBounds();

    std::vector<Bullet> getBullets();

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void shoot();

    float speed = 300.f;

    int hp;

    sf::RectangleShape form;

    std::vector<sf::RectangleShape> hpBar;

    TextureManager texture;

    sf::FloatRect windowBounds;

    sf::Clock clock;

    sf::Time frameTime;

    PlayerPatterns::Pattern pattern;

    sf::Text *coolDownSec;

    sf::Font *font;

    bool charged;

    int coolDown;

    sf::Clock coolDownClock;

    sf::Clock timer;

    std::vector<Bullet> bullets;
};


#endif //SFMLGAME_PLAYER_H
