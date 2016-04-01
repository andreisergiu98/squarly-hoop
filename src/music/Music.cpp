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

#include <fstream>
#include "Music.h"

Music::Music() {
    SoundController::Instance()->loadSystem();
    currentSong = 0;
}

void Music::start() {
    sound->setStarted(true);
}

void Music::update() {
    SoundController::Instance()->update();

    if (!sound->isPlaying()) {
        next();
    }
}

bool Music::getBeat() {
    if (localLastBeatOccured != SoundController::Instance()->getLastBeat()) {
        localLastBeatOccured = SoundController::Instance()->getLastBeat();
        return true;
    }
    return false;
}

float Music::getFreq() {
    return sound->getFreq();
}


void Music::loadPlaylist(std::string location) {
    if (!std::ifstream("playlist")) {
        debug::print("error playlist not found");
        return;
    }

    std::ifstream fin(location);

    while (fin) {
        std::string a;
        getline(fin, a);
        playlist.push_back(a);
    }

    if (!playlist.size()) {
        debug::print("error empty playlist");
    }
}

void Music::next() {
    currentSong++;
    if (currentSong >= playlist.size() - 1)
        currentSong = 0;
    std::string location = std::string("../res/music/" + playlist[currentSong]);
    char *cstr = &location[0u];
    SoundController::Instance()->loadSong(1024, cstr);
    start();
}

void Music::restart() {
    std::string location = std::string("../res/music/" + playlist[0]);
    char *cstr = &location[0u];
    SoundController::Instance()->loadSong(1024, cstr);
    start();
}

void Music::pause() {
    sound->setPaused(true);
}

void Music::resume() {
    sound->setPaused(false);
}
















