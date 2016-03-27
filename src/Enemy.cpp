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

#include "Enemy.h"
#include "Utils.h"

Enemy::Enemy(sf::Vector2f position, sf::Vector2f destination, TextureManager *texture, float speed) {
    form.setPosition(position);
    form.setSize(sf::Vector2f(31, 31));

    this->texture = texture;

    color = rand() % 6 + 1;

    form.setTexture(&this->texture->getTexture("../res/textures/enemy" + intToStr(color) + ".png"));
    form.setOrigin(15.5, 15.5);

    hp = rand() % 3 + 1;

    this->destination = destination;

    velocity = calcVelocity(position, destination);
    velocity *= speed;

    this->speed = speed;
}

void Enemy::update(sf::Time frameTime) {
    this->frameTime = frameTime;
}

void Enemy::process() {
    if (getPosition().y < destination.y)
        form.move(velocity * frameTime.asSeconds());

    form.rotate(10);

    bullets.clear();

    if (beat) {
        shoot();
        clock.restart();
        beat = false;
    }
}

void Enemy::shoot() {
    int color = rand() % 6 + 1;

    bullets.clear();
    if (freq < 4.f)
        bullets = EnemyPatterns::getBullets(EnemyPatterns::Pattern::SIMPLE, getPosition(), target, 200.f,
                                            texture->getTexture(
                                                    std::string("../res/textures/bullet2" + intToStr(color) + ".png")),
                                            color);

    if (freq > 4.f && freq < 6.f) {
        bullets = EnemyPatterns::getBullets(EnemyPatterns::Pattern::SPREAD, getPosition(), target, 200.f,
                                            texture->getTexture(
                                                    std::string("../res/textures/bullet2" + intToStr(color) + ".png")),
                                            color);
    }
    if (freq > 6.f) {
        bullets = EnemyPatterns::getBullets(EnemyPatterns::Pattern::CIRCLE, getPosition(), target, 200.f,
                                            texture->getTexture(
                                                    std::string("../res/textures/bullet2" + intToStr(color) + ".png")),
                                            color);
    }
}

void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(form);
}

sf::FloatRect Enemy::getGlobalBounds() {
    return form.getGlobalBounds();
}

std::vector<Bullet> Enemy::getBullets() {
    return bullets;
}

sf::Vector2f Enemy::getPosition() {
    return form.getPosition();
}

unsigned short int Enemy::getColor() {
    return color;
}

sf::Vector2f Enemy::getSize() {
    return form.getSize();
}

int Enemy::getHp() {
    return hp;
}

void Enemy::setHp(int i) {
    hp = i;
}

void Enemy::updateTarget(sf::Vector2f target) {
    this->target = target;
}

void Enemy::updateBeat(bool beat, float freq) {
    this->beat = beat;
    this->freq = freq;
}
