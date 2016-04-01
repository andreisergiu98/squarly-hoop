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
    texture.setSmooth(smoothTextures);

    if (texture.loadFromFile(texLocation)) {
        textures[texLocation] = texture;
        debug::print("loading image", texLocation);
        return textures[texLocation];
    }

    textures[texLocation] = texture;

    return textures[texLocation];
}

void TextureManager::deleteTexture(sf::Texture &texture) {
    for (auto it = textures.begin(); it != textures.end(); ++it) {
        if (&texture == &it->second) {
            debug::print("deleting image", it->first);
            textures.erase(it);
        }
    }
}

void TextureManager::deleteTexture(std::string texLocation) {
    auto it = textures.find(texLocation);
    if (it != textures.end()) {
        debug::print("deleting image", texLocation);
        textures.erase(it);
    }
}

void TextureManager::setSmoothTextures(bool smth) {
    smoothTextures = smth;

    for (auto it = textures.begin(); it != textures.end(); ++it) {
        it->second.setSmooth(smoothTextures);
    }
}


