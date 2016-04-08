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

#include <sstream>
#include "EntityManager.h"
#include "Utilities.h"

EntityManager::EntityManager(sf::FloatRect windowBounds, TextureManager *textureManager) {
    texture = textureManager;
    this->windowBounds = windowBounds;
    isPlayerHit = false;
    destroyedEnemies = 0;
    maxSpawnNumber = 3;

    explosionSound->loadSound("../res/sounds/explosion.wav");
    explosionSound->setVolume(1.f);
}

void EntityManager::spawn() {
    updateSpawnLocations();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(50, (int) (windowBounds.width / 3.f - 50));
    int val = distribution(gen);

    if (spawnLeft) {
        float x = val;
        float y = -(rand() % 60 + 35);
        Enemy enemy(sf::Vector2f(x, y), sf::Vector2f(x, -y), texture, 200.f);
        enemies.push_back(enemy);
    }

    else if (spawnCenter) {
        float x = val + windowBounds.width / 3.f;
        float y = -(rand() % 60 + 35);
        Enemy enemy(sf::Vector2f(x, y), sf::Vector2f(x, -y), texture, 200.f);
        enemies.push_back(enemy);
    }

    else if (spawnRight) {
        float x = val + windowBounds.width / 3.f * 2.f;
        float y = -(rand() % 60 + 35);
        Enemy enemy(sf::Vector2f(x, y), sf::Vector2f(x, -y), texture, 200.f);
        enemies.push_back(enemy);
    }

    maxSpawnNumber = rand() % 2 + 1;
}

void EntityManager::updateSpawnLocations() {
    spawnLeft = true;
    spawnRight = true;
    spawnCenter = true;

    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        if (it->getPosition().x >= windowBounds.width / 3.f * 2.f) {
            spawnRight = false;
        }
        else if (it->getPosition().x >= windowBounds.width / 3.f) {
            spawnCenter = false;
        }
        else if (it->getPosition().x >= 0) {
            spawnLeft = false;
        }
    }
}

void EntityManager::update(sf::Time frameTime) {
    if (enemies.size() <= maxSpawnNumber)
        spawn();

    clean();

    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        push_enemy_bullets(it->getBullets());
    }

    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        it->update(frameTime);
    }

    for (auto it = enemyBullets.begin(); it != enemyBullets.end(); ++it) {
        it->update(frameTime);
    }

    for (auto it = playerBullets.begin(); it != playerBullets.end(); ++it) {
        it->update(frameTime);
    }

    for (auto it = explosions.begin(); it != explosions.end(); ++it) {
        it->update();
    }
}

void EntityManager::update(Player &player) {
    push_player_bullets(player.getBullets());

    if (isPlayerHit) {
        player.gotDamage();
        isPlayerHit = !isPlayerHit;
    }
    playerBounds = player.getGlobalBounds();

    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        it->updateTarget(player.getPosition());
    }
}

void EntityManager::clean() {

    for (auto it = enemies.begin(); it != enemies.end();) {
        if (it->getPosition().y > windowBounds.height + 31)
            it = enemies.erase(it);
        else {
            ++it;
        }
    }

    for (auto it = enemyBullets.begin(); it != enemyBullets.end();) {
        if (!it->getGlobalBounds().intersects(windowBounds))
            it = enemyBullets.erase(it);
        else {
            ++it;
        }

    }

    for (auto it = playerBullets.begin(); it != playerBullets.end();) {
        if (!it->getGlobalBounds().intersects(windowBounds))
            it = playerBullets.erase(it);
        else {
            ++it;
        }
    }
    for (auto it = explosions.begin(); it != explosions.end();) {
        if (it->destroy())
            it = explosions.erase(it);
        else
            ++it;
    }
}

void EntityManager::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto it = enemies.begin(); it != enemies.end(); it++) {
        target.draw(*it);
    }

    for (auto it = enemyBullets.begin(); it != enemyBullets.end(); ++it) {
        target.draw(*it);
    }

    for (auto it = playerBullets.begin(); it != playerBullets.end(); ++it) {
        target.draw(*it);
    }

    for (auto it = explosions.begin(); it != explosions.end(); ++it) {
        target.draw(*it);
    }
}

void EntityManager::process() {
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        it->process();
    }

    for (auto it = enemyBullets.begin(); it != enemyBullets.end(); ++it) {
        it->process();
    }

    for (auto it = playerBullets.begin(); it != playerBullets.end(); ++it) {
        it->process();
    }

    collision();
}


void EntityManager::collision() {
    for (auto it1 = enemies.begin(); it1 != enemies.end(); ++it1) {
        for (auto it2 = playerBullets.begin(); it2 != playerBullets.end();) {
            if (it2->getGlobalBounds().intersects(it1->getGlobalBounds())) {
                int t = rand() % 3 + 1;
                Explosion expl(it2->getPosition(), it2->getSize(), texture->getTexture(
                        "../res/textures/explosion" + utilities::intToStr(it2->getColor()) + utilities::intToStr(t) + ".png"));
                explosions.push_back(expl);

                it2 = playerBullets.erase(it2);
                it1->setHp(it1->getHp() - 1);
            }
            else {
                it2++;
            }
        }
    }

    destroyedEnemies = 0;
    for (auto it = enemies.begin(); it != enemies.end();) {
        if (it->getHp() <= 0) {
            int t = rand() % 3 + 1;
            Explosion expl(it->getPosition(), it->getSize(), texture->getTexture(
                    "../res/textures/explosion" + utilities::intToStr(it->getColor()) + utilities::intToStr(t) + ".png"));
            explosions.push_back(expl);
            it = enemies.erase(it);

            explosionSound->play();
            destroyedEnemies++;
        }
        else {
            it++;
        }
    }

    for (auto it = enemyBullets.begin(); it != enemyBullets.end();) {
        if (playerBounds.intersects(it->getGlobalBounds())) {
            int t = rand() % 3 + 1;
            Explosion expl(it->getPosition(), it->getSize(), texture->getTexture(
                    "../res/textures/explosion" + utilities::intToStr(it->getColor()) + utilities::intToStr(t) + ".png"));
            explosions.push_back(expl);

            it = enemyBullets.erase(it);
            isPlayerHit = true;
        }
        else {
            it++;
        }
    }
}

void EntityManager::push_player_bullets(std::vector<Bullet> bullets) {
    for (auto it = bullets.begin(); it != bullets.end(); ++it)
        playerBullets.push_back(*it);
}

void EntityManager::push_enemy_bullets(std::vector<Bullet> bullets) {
    for (auto it = bullets.begin(); it != bullets.end(); ++it)
        enemyBullets.push_back(*it);
}

void EntityManager::clear() {
    enemies.clear();
    enemyBullets.clear();
    playerBullets.clear();
    explosions.clear();
}

int EntityManager::getDestroyedEnemies() {
    return destroyedEnemies;
}

void EntityManager::updateBeat(bool beat, float freq) {
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        it->updateBeat(beat, freq);
    }
}
