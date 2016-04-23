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

#ifndef SFMLGAME_ENTITIESMANAGER_H
#define SFMLGAME_ENTITIESMANAGER_H

#include <random.hpp>
#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"
#include "TextureManager.h"
#include "Explosion.h"
#include "Particle.h"

class EntityManager : public sf::Drawable {
public:
    EntityManager() { }

    EntityManager(sf::FloatRect windowBounds, TextureManager *textureManager);

    void clear();

    void process();

    void updateBeat(bool beat, float freq);

    void update(sf::Time frameTime);

    void update(Player &player);

    int getDestroyedEnemies();

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void spawn();

    void clean();

    void collision();

    void updateSpawnLocations();

    void push_player_bullets(std::vector<Bullet>);

    void push_enemy_bullets(std::vector<Bullet>);

    std::vector<Enemy> enemies;
    std::vector<Bullet> enemyBullets;
    std::vector<Bullet> playerBullets;
    std::vector<Explosion> explosions;

    sf::FloatRect windowBounds;
    sf::FloatRect playerBounds;

    boost::mt19937 generator;

    ParticleSystem *particle;

    bool isPlayerHit;

    bool spawnLeft, spawnRight, spawnCenter;

    int destroyedEnemies;

    int maxSpawnNumber;

    Sound *explosionSound = new Sound();

    TextureManager *texture;
};


#endif //SFMLGAME_ENTITIESMANAGER_H
