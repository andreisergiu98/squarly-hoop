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

#include "TextureManager.h"

sf::Texture &TextureManager::getTexture(const std::string &texLocation) {
    for (auto it = textures.begin(); it != textures.end(); ++it) {
        if (texLocation == it->first) {
            return it->second;
        }
    }

    sf::Texture texture;
    texture.setSmooth(true);

    if (texture.loadFromFile(texLocation)) {
        textures[texLocation] = texture;
        std::cout << "DEBUG_MESSAGE: loading image: " << texLocation << "\n";
        return textures[texLocation];
    }

    std::cout << "GAME_ERROR: Image: \"" << texLocation << "\" was not found. It is filled with an empty image.\n";

    textures[texLocation] = texture;

    return textures[texLocation];
}

void TextureManager::deleteTexture(sf::Texture &texture) {
    for (auto it = textures.begin(); it != textures.end(); ++it) {
        if (&texture == &it->second) {
            textures.erase(it);
        }
    }
}

void TextureManager::deleteTexture(std::string texLocation) {
    auto it = textures.find(texLocation);
    if (it != textures.end()) {
        textures.erase(it);
    }
}
