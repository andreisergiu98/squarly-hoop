//
// Created by andrei on 3/12/16.
//

#include "Music.h"

Music::Music() {
    BeatDetector::Instance()->loadSystem();

}

void Music::loadMusic(char * location) {
    BeatDetector::Instance()->LoadSong(1024, location);
}

void Music::play() {
    beat->setStarted(true);
}

void Music::update() {
    BeatDetector::Instance()->update();
}

bool Music::getBeat() {
    if(localLastBeatOccured != BeatDetector::Instance()->getLastBeat())
    {
        localLastBeatOccured = BeatDetector::Instance()->getLastBeat();
        return true;
    }
    return false;
}

float Music::getFreq() {
    return beat->getFreq();
}
