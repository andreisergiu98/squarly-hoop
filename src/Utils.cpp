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

#include <math.h>
#include "Utils.h"

std::string intToStr(int a) {
    std::stringstream ss;
    ss << a;
    std::string str = ss.str();

    return str;
}


float distance(sf::Vector2f a, sf::Vector2f b) {
    float dist = (float) sqrt((b.x - a.x) * (b.x - a.x) +
                              (b.y - a.y) * (b.y - a.y));
    return dist;
}

sf::Vector2f calcVelocity(sf::Vector2f a, sf::Vector2f b) {
    sf::Vector2f velocity;

    float dist = distance(a, b);

    velocity.x = (b.x - a.x) / dist;
    velocity.y = (b.y - a.y) / dist;

    return velocity;
}