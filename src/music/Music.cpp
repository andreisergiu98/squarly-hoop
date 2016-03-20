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
    BeatDetector::Instance()->loadSystem();
    currentSong = 0;
}

void Music::loadMusic(std::string location) {
    char *cstr = &location[0u];
    BeatDetector::Instance()->LoadSong(1024, cstr);
}

void Music::play() {
    beat->setStarted(true);
}

void Music::update() {
    BeatDetector::Instance()->update();

    if (!beat->isPlaying()) {
        next();
    }
}


bool Music::getBeat() {
    if (localLastBeatOccured != BeatDetector::Instance()->getLastBeat()) {
        localLastBeatOccured = BeatDetector::Instance()->getLastBeat();
        return true;
    }
    return false;
}

float Music::getFreq() {
    return beat->getFreq();
}


void Music::loadPlaylist(std::string location) {
    std::ifstream fin(location);

    while (fin) {
        std::string a;
        getline(fin, a);
        playlist.push_back(a);
    }

    loadMusic((std::string("../res/music/" + playlist[0])));
}

void Music::next() {
    currentSong++;
    if (currentSong >= playlist.size() - 1)
        currentSong = 0;
    std::string location = std::string("../res/music/" + playlist[currentSong]);
    char *cstr = &location[0u];
    BeatDetector::Instance()->loadNewSong(1024, cstr);
    play();

}

void Music::restart() {
    std::string location = std::string("../res/music/" + playlist[0]);
    char *cstr = &location[0u];
    BeatDetector::Instance()->loadNewSong(1024, cstr);
    play();
}
