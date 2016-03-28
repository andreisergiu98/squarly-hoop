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

#ifndef BEAT_DETECTOR
#define BEAT_DETECTOR

#include <algorithm>
#include <queue>
#include <time.h>
#include <array>
#include <math.h>
#include "fmod.hpp"
#include "fmod_errors.h"
#include "../DebugHelper.h"

class BeatDetector {
public:
    ~BeatDetector();

    void loadSystem();

    void loadSong(int, char *);

    void update();

    void setPaused(FMOD_BOOL pause);

    void setStarted(FMOD_BOOL);

    bool isPlaying();

    char *getLastBeat();

    float getFreq();

    static BeatDetector *Instance() {
        if (instance == 0) {
            instance = new BeatDetector();
        }
        return instance;
    }

private:
    BeatDetector() { };

    FMOD_SYSTEM *fmodSetup();

    void updateTime();

    float *getCurrentSpectrum();

    float calculateFluxAndSmoothing(float *);

    void FMODErrorCheck(FMOD_RESULT);

    static BeatDetector *instance;
    FMOD_SYSTEM *system;
    int sampleSize;
    int test;
    float sampleRate;
    unsigned int seconds;
    unsigned int minutes;
    FMOD_BOOL areWePlaying;
    float *previousFFT;
    float specFlux;
    float difference;
    unsigned int timeBetween;
    const char *songString;
    FMOD_BOOL started;
    char *lastBeatRegistered;

    FMOD_SOUND *audio;
    FMOD_CHANNELGROUP *channelMusic;
    FMOD_CHANNEL *songChannel1;
    FMOD_CHANNEL *songChannel2;
    bool delayedSong = false;
    int timeToDelay;

    int initialTime;
    int currentTime;
    int currentMillis;
    int currentSeconds;
    int lastSeconds;
    int currentMinutes;

    std::vector<float> spectrumFluxes;
    std::vector<float> smootherValues;
    float median;
    float smoothMedian;
    float beatThreshold;
    float thresholdSmoother;

    float freq;
};

#endif
