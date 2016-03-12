//
// Created by andrei on 3/12/16.
//

#ifndef SFMLGAME_MUSIC_H
#define SFMLGAME_MUSIC_H

#include "BeatDetector.h"

class Music {

public:
    Music();

    void loadMusic(char * location);

    void update();

    bool getBeat();

    float getFreq();

    void play();

private:
    BeatDetector *beat = BeatDetector::Instance();

    TimeStamp *localLastBeatOccured;
};


#endif //SFMLGAME_MUSIC_H
