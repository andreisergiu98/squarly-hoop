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
#include "Player.h"
#include "Utils.h"

Player::Player(sf::FloatRect windowBounds) {
    form.setTexture(&texture.getTexture("../res/Textures/player.png"));
    form.setPosition(200, 200);
    form.setSize(sf::Vector2f(31, 31));
    form.setOrigin(sf::Vector2f(15.5, 15.5));

    windowBounds.top += form.getSize().x;
    windowBounds.left += form.getSize().y;
    windowBounds.width -= 2 * form.getSize().x + 5;
    windowBounds.height -= 2 * form.getSize().y + 5;

    this->windowBounds = windowBounds;

    hp = 5;
}

void Player::update(sf::Time frameTime) {
    this->frameTime = frameTime;
    for (auto it = bullets.begin(); it != bullets.end(); ++it) {
        it->update(frameTime);
    }
}

void Player::setSpeed(float speed) {
    this->speed = speed;
}

void Player::process() {
    sf::Vector2f velocity;

    bullets.clear();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) or sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        velocity.y -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) or sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        velocity.y += speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) or sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        velocity.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        velocity.x += speed;


    if (clock.getElapsedTime().asMilliseconds() >= 200) {
        shoot();
        clock.restart();
    }

    if (velocity.x != 0.f and velocity.y != 0.f)
        velocity /= std::sqrt(2.f);

    form.move(velocity * frameTime.asSeconds());

    if (!getGlobalBounds().intersects(windowBounds)) {
        form.move(-velocity * frameTime.asSeconds());

        if (velocity.x != 0.f and velocity.y != 0.f) {
            velocity *= std::sqrt(2.f);

            form.move(sf::Vector2f(velocity.x, 0) * frameTime.asSeconds());
            if (!getGlobalBounds().intersects(windowBounds)) {
                form.move(-sf::Vector2f(velocity.x, 0) * frameTime.asSeconds());
            }

            form.move(sf::Vector2f(0, velocity.y) * frameTime.asSeconds());
            if (!getGlobalBounds().intersects(windowBounds)) {
                form.move(-sf::Vector2f(0, velocity.y) * frameTime.asSeconds());
            }
        }
    }

    form.rotate(60);

    for (auto it = bullets.begin(); it != bullets.end(); ++it) {
        it->process();
    }
}

void Player::shoot() {
    int t = rand() % 6 + 1;

    bullets = getBulletsPatern(ShootingPatern::SPREAD, form.getPosition(),
                               sf::Vector2i((int) form.getPosition().x, (int) (form.getPosition().y - 300)), 300.f,
                               texture.getTexture(std::string("../res/Textures/bullet1" + intToStr(t) + ".png")), t);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(form);
}

void Player::updateMousePosition(sf::Vector2i mousePosition) {
    this->mousePosition = mousePosition;
}

std::vector<Bullet> Player::getBullets() {
    return bullets;
}

sf::FloatRect Player::getGlobalBounds() {
    sf::FloatRect boundingBox = form.getGlobalBounds();
    boundingBox.top += 9;
    boundingBox.left += 9;
    boundingBox.height -= 20;
    boundingBox.width -= 20;

    return boundingBox;
}

int Player::getHp() {
    return hp;
}

void Player::setHp(int hp) {
    this->hp = hp;
}
