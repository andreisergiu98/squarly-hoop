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
#include "Utils.h"

EntityManager::EntityManager(sf::FloatRect windowBounds) {
    this->windowBounds = windowBounds;
    isPlayerHit = false;
}

void EntityManager::spawn() {
    if (enemies.size() <= 1) {
        int nr = 0;
        if (spawnClock.getElapsedTime().asMilliseconds() > 200) {
            nr = (unsigned short) (rand() % 3 + 1);
            spawnClock.restart();
        }

        enum Side {
            left, right
        };
        Side side = left;

        for (int i = 0; i < nr; i++) {
            float x, y;
            x = rand() % (int) (windowBounds.width - 20) + 20;
            y = rand() % 80 + 0;
            y -= 100;

            sf::Vector2f dest(x, -2 * y);

            sf::Vector2f pos(x, y);
            Enemy enemy(pos, dest, texture, 100.f);
            enemies.push_back(enemy);
        }
    }
}

void EntityManager::update(sf::Time frameTime) {
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

void EntityManager::move() {
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        it->process();
    }

    for (auto it = enemyBullets.begin(); it != enemyBullets.end(); ++it) {
        it->process();
    }

    for (auto it = playerBullets.begin(); it != playerBullets.end(); ++it) {
        it->process();
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

void EntityManager::push_player_bullets(std::vector<Bullet> bullets) {
    for (auto it = bullets.begin(); it != bullets.end(); ++it)
        playerBullets.push_back(*it);
}

void EntityManager::push_enemy_bullets(std::vector<Bullet> bullets) {
    for (auto it = bullets.begin(); it != bullets.end(); ++it)
        enemyBullets.push_back(*it);
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
    move();

    collision();
}


void EntityManager::collision() {
    for (auto it1 = enemies.begin(); it1 != enemies.end(); ++it1) {
        for (auto it2 = playerBullets.begin(); it2 != playerBullets.end();) {
            if (it2->getGlobalBounds().intersects(it1->getGlobalBounds())) {
                int t = rand() % 3 + 1;
                Explosion expl1(it1->getPosition(), it1->getSize(), texture.getTexture(
                        "../res/Textures/explosion" + intToStr(it1->getId()) + intToStr(t) + ".png"));
                Explosion expl2(it2->getPosition(), it2->getSize(), texture.getTexture(
                        "../res/Textures/explosion" + intToStr(it2->getId()) + intToStr(t) + ".png"));
                explosions.push_back(expl1);
                explosions.push_back(expl2);

                it2 = playerBullets.erase(it2);
                it1->setHp(it1->getHp() - 1);
            }
            else {
                it2++;
            }
        }
    }

    for (auto it = enemies.begin(); it != enemies.end();) {
        if (it->getHp() <= 0) {
            it = enemies.erase(it);
        }
        else {
            it++;
        }
    }

    for (auto it = enemyBullets.begin(); it != enemyBullets.end();) {
        if (playerBounds.intersects(it->getGlobalBounds())) {
            int t = rand() % 3 + 1;
            Explosion expl(it->getPosition(), it->getSize(), texture.getTexture(
                    "../res/Textures/explosion" + intToStr(it->getId()) + intToStr(t) + ".png"));
            explosions.push_back(expl);

            it = enemyBullets.erase(it);
            isPlayerHit = true;
        }
        else {
            it++;
        }
    }
}

void EntityManager::update(Player &player) {
    push_player_bullets(player.getBullets());
    playerBounds = player.getGlobalBounds();
    if (isPlayerHit) {
        player.setHp(player.getHp() - 1);
        isPlayerHit = !isPlayerHit;
    }
}

void EntityManager::clear() {
    enemies.clear();
    enemyBullets.clear();
    playerBullets.clear();
    explosions.clear();
}
