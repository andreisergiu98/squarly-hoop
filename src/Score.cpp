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

#include "Score.h"
#include "Utils.h"

Score::Score(sf::FloatRect windowBounds) {

    text = new sf::Text;
    font = new sf::Font;

    text->setPosition(3, windowBounds.height - 40);
    text->setScale(0.4, 0.4);
    text->setString("Score: 0");
    font->loadFromFile("../res/fonts/OpenSans-Bold.ttf");
    text->setFont(*font);
    score = 0;
}


void Score::setScore(unsigned  int score) {
    if (this->score != 0)
        text->setString("Score: " + intToStr(score) + "00");
    this->score = score;
}

unsigned int Score::getScore() {
    return score;
}

void Score::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*text);
}

void Score::reset() {
    text->setString("Score: 0");
    score = 0;
}
