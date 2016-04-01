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

#ifndef SFMLGAME_MUSIC_H
#define SFMLGAME_MUSIC_H

#include <SFML/System/Clock.hpp>
#include "SoundController.h"

class Music {

public:
    Music();

    void update();

    void next();

    void restart();

    void resume();

    void pause();

    bool getBeat();

    float getFreq();

    void start();

    void loadPlaylist(std::string location);

private:
    SoundController *beat = SoundController::Instance();

    char *localLastBeatOccured;

    std::vector<std::string> playlist;

    int currentSong;
};


#endif //SFMLGAME_MUSIC_H
