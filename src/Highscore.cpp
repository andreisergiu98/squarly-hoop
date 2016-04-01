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

#include "Highscore.h"
#include "Utilities.h"

Highscore::Highscore() {
    text = new sf::Text;
    font = new sf::Font;

    font->loadFromFile("../res/fonts/OpenSans-Bold.ttf");
    text->setFont(*font);
    text->setPosition(5, 5);
    text->setScale(0.5, 0.5);
    text->setString("Highscore: 0");

    if (!std::ifstream(".highscore")) {
        highscore = 0;
    }
    else{
        std::ifstream readFile(".highscore");
        readFile >> highscore;
        text->setString("Highscore: " + utilities::intToStr(highscore) + "00");
        readFile.close();
    }
}

void Highscore::update(unsigned int score) {
    if(score > highscore){
        highscore = score;
        text->setString("Highscore: " + utilities::intToStr(highscore) + "00");
        std::ofstream writeToFile(".highscore");
        writeToFile << highscore;
        writeToFile.close();
    }
}

void Highscore::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*text);
}









