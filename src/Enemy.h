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

#ifndef SFMLGAME_ENEMY_H
#define SFMLGAME_ENEMY_H

#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Bullet.h"
#include "ShootingPaterns.h"

class Enemy : public sf::Drawable {
public:
    Enemy(sf::Vector2f position, sf::Vector2f destination, TextureManager &texture, float speed);

    void update(sf::Time frameTime);

    void updateTarget(sf::Vector2f target);

    void updateBeat(bool beat, float freq);

    std::vector<Bullet> getBullets();

    sf::Vector2f getPosition();

    sf::Vector2f getSize();

    int getHp();

    void setHp(int);

    void process();

    void shoot();

    unsigned short int getColor();

    sf::FloatRect getGlobalBounds();

private:
    sf::RectangleShape form;

    sf::Time frameTime;

    sf::Vector2f velocity;

    sf::Vector2f destination;

    sf::Vector2f target;

    std::vector<Bullet> bullets;

    sf::Clock clock;

    bool beat = false;

    float freq;

    TextureManager *texture;
    int c;
    int hp;

    unsigned short int color;

    float speed;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};


#endif //SFMLGAME_ENEMY_H
