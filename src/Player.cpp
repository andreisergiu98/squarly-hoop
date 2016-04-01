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
#include "Utilities.h"

Player::Player(sf::FloatRect windowBounds, TextureManager *textureManager) {
    texture = textureManager;

    form.setTexture(&texture->getTexture("../res/textures/player.png"));
    form.setPosition(480, windowBounds.height - 40);
    form.setSize(sf::Vector2f(31, 31));
    form.setOrigin(sf::Vector2f(15.5, 15.5));
    core.setTexture(&texture->getTexture("../res/textures/player-core.png"));
    core.setPosition(form.getPosition());
    core.setSize(sf::Vector2f(12, 12));
    core.setOrigin(6, 6);

    shield.setSize(sf::Vector2f(600, 600));
    shield.setTexture(&texture->getTexture("../res/textures/shield.png"));
    shield.setOrigin(300, 300);

    this->windowBounds = windowBounds;

    hp = 10;
    for (int i = 0; i < hp; i++) {
        sf::RectangleShape rect;
        rect.setPosition(5 + i * 20, windowBounds.height - 20);
        rect.setSize(sf::Vector2f(10, 10));
        rect.setTexture(&texture->getTexture("../res/textures/heart.png"));
        hpBar.push_back(rect);
    }

    pattern = playerPatterns::Pattern::SIMPLE;
    charged = true;

    coolDownSec = new sf::Text;
    font = new sf::Font;
    coolDownSec->setPosition(windowBounds.width - 60, windowBounds.height - 20);
    coolDownSec->setScale(0.4, 0.4);
    coolDownSec->setString("Charged");
    font->loadFromFile("../res/fonts/OpenSans-Bold.ttf");
    coolDownSec->setFont(*font);

    damaged = false;
    shielded = false;
}

void Player::update(sf::Time frameTime) {
    this->frameTime = frameTime;
    for (auto it = bullets.begin(); it != bullets.end(); ++it) {
        it->update(frameTime);
    }
}

void Player::process() {
    sf::Vector2f velocity;

    bullets.clear();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        velocity.y -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        velocity.y += speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        velocity.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        velocity.x += speed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
        charged = true;
        abilitiesCooldown.restart();
        timer.restart();
        coolDownSec->setPosition(windowBounds.width - 60, windowBounds.height - 20);
        coolDownSec->setString("Charged");
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
        setHp(10);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        if (charged) {
            pattern = playerPatterns::SPREAD;
            charged = false;
            coolDown = 36;
            timer.restart();
            abilitiesCooldown.restart();
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        if (charged) {
            pattern = playerPatterns::SPREADMAX;
            charged = false;
            coolDown = 51;
            timer.restart();
            abilitiesCooldown.restart();
        }
    }

    if (!charged) {
        coolDownSec->setPosition(windowBounds.width - 90, windowBounds.height - 20);
        coolDownSec->setString(
                "Cooldown : " + utilities::intToStr((int) (coolDown - abilitiesCooldown.getElapsedTime().asSeconds())));
    }

    if (timer.getElapsedTime().asSeconds() >= 10) {
        pattern = playerPatterns::Pattern::SIMPLE;
    }

    if (abilitiesCooldown.getElapsedTime().asSeconds() >= coolDown) {
        coolDownSec->setPosition(windowBounds.width - 60, windowBounds.height - 20);
        coolDownSec->setString("Charged");
        charged = true;
    }

    if (clock.getElapsedTime().asMilliseconds() >= 100 && hp > 0) {
        if (!shielded) {
            shoot();
        }
        clock.restart();
    }

    if (velocity.x != 0.f && velocity.y != 0.f)
        velocity /= std::sqrt(2.f);

    form.move(velocity * frameTime.asSeconds());

    int xMin = 15, xMax = (int) (windowBounds.width - 15), yMin = 15, yMax = (int) (windowBounds.height - 35);

    if (form.getPosition().x < xMin || form.getPosition().x > xMax || form.getPosition().y < yMin ||
        form.getPosition().y > yMax) {
        form.move(-velocity * frameTime.asSeconds());

        if (velocity.x != 0.f && velocity.y != 0.f) {
            velocity *= std::sqrt(2.f);

            form.move(sf::Vector2f(velocity.x, 0) * frameTime.asSeconds());
            if (form.getPosition().x < xMin || form.getPosition().x > xMax || form.getPosition().y < yMin ||
                form.getPosition().y > yMax) {
                form.move(-sf::Vector2f(velocity.x, 0) * frameTime.asSeconds());
            }

            form.move(sf::Vector2f(0, velocity.y) * frameTime.asSeconds());
            if (form.getPosition().x < xMin || form.getPosition().x > xMax || form.getPosition().y < yMin ||
                form.getPosition().y > yMax) {
                form.move(-sf::Vector2f(0, velocity.y) * frameTime.asSeconds());
            }
        }
    }

    if (damageClock.getElapsedTime().asMilliseconds() > 500) {
        damaged = false;
    }
    if (shieldCooldown.getElapsedTime().asMilliseconds() > 3000) {
        shielded = false;
    }

    core.setPosition(form.getPosition());
    shield.setPosition(form.getPosition());

    form.rotate(20);
    shield.rotate(5);
    core.rotate(-20);
}

void Player::shoot() {
    int t = rand() % 6 + 1;

    bullets = playerPatterns::getBullets(pattern, form.getPosition(), 400.f, texture->getTexture(
            std::string("../res/textures/bullet1" + utilities::intToStr(t) + ".png")), t);
}

std::vector<Bullet> Player::getBullets() {
    return bullets;
}

sf::FloatRect Player::getGlobalBounds() {
    if (shielded) {
        sf::FloatRect boundingBox = shield.getGlobalBounds();
        boundingBox.top += 200;
        boundingBox.left += 200;
        boundingBox.height -= 400;
        boundingBox.width -= 400;

        return boundingBox;
    }

    return core.getGlobalBounds();
}

int Player::getHp() {
    return hp;
}

void Player::setHp(int hp) {
    this->hp = hp;
}

sf::Vector2f Player::getPosition() {
    return form.getPosition();
}

void Player::reset() {
    form.setPosition(windowBounds.width / 2.f - 20, windowBounds.height - 40);
    abilitiesCooldown.restart();
    timer.restart();
    coolDown = 0;
    charged = true;
    shielded = false;
    hp = 10;
}

void Player::gotDamage() {
    if (!shielded) {
        hp--;
        shielded = true;
        shieldCooldown.restart();
    }
    damaged = true;
    damageClock.restart();
}

bool Player::isDamaged() {
    return damaged;
}

void Player::setPosition(sf::Vector2f pos) {
    form.setPosition(pos);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(form);
    target.draw(core);
    for (int i = 0; i < hp; i++) {
        target.draw(hpBar[i]);
    }
    if (shielded) {
        target.draw(shield);
    }
    target.draw(*coolDownSec);
}




