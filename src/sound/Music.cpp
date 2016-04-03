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
    if (!boost::filesystem::exists("playlist")) {
        debug::print("custom playlist not found, loading all files from sound/");
        playlist = getSongList();
    }
    else {
        debug::print("found custom playlist, loading your list");
        playlist = getCustomSongList(location);
    }
    if (!playlist.size()) {
        debug::print("ERROR no songs found... exiting");
        exit(-1);
    }
}

void Music::next() {
    currentSong++;
    if (currentSong >= playlist.size() - 1)
        currentSong = 0;

    std::string location = std::string(playlist[currentSong]);
    char *c_str = &location[0u];
    SoundController::Instance()->loadSong(1024, c_str);
    start();
}

void Music::restart() {
    std::string location = std::string(playlist[0]);
    char *c_str = &location[0u];
    SoundController::Instance()->loadSong(1024, c_str);
    start();
}

void Music::pause() {
    sound->setPaused(true);
}

void Music::resume() {
    sound->setPaused(false);
}

std::vector<std::string> Music::getSongList() {
    boost::filesystem::directory_iterator end_it;
    boost::filesystem::path path("../res/music/");
    std::vector<std::string> list;

    for (boost::filesystem::directory_iterator it(path); it != end_it; ++it) {
        if (is_regular_file(it->path())) {
            std::string currentFile = it->path().string();
            list.push_back(currentFile);
            debug::print("found", currentFile);
        }
    }

    return list;
}

std::vector<std::string> Music::getCustomSongList(std::string location) {
    std::ifstream fin(location);
    std::vector<std::string> list;

    while (!fin.eof()) {
        std::string file;
        getline(fin, file);
        file = "../res/music/" + file;

        boost::filesystem::path path(file);

        if (is_regular_file(path)) {
            debug::print("found", file);
            list.push_back(file);
        }
        else {
            if (file != "../res/music/")
                debug::print("ERROR song", file, "not found");
        }
    }

    return list;
}




















