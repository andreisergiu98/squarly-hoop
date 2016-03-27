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

#ifndef SFMLGAME_TEXTURES_H
#define SFMLGAME_TEXTURES_H

#include <SFML/Graphics/Texture.hpp>
#include <map>
#include "DebugHelper.h"

class TextureManager {
public:
    TextureManager() { }

    sf::Texture &getTexture(const std::string &texLocation);

    void deleteTexture(sf::Texture &texture);

    void deleteTexture(std::string texLocation);

    void setSmoothTextures(bool smth);
private:
    std::map<std::string, sf::Texture> textures;

    bool smoothTextures;

    DebugHelper debug;
};


#endif //RPGGAME_TEXTURES_H
