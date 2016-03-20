////////////////////////////////////////////////////////////
//
//      Copyright (c) 2015 Padraig O Connor
//
//      Permission is hereby granted, free of charge, to any person obtaining a copy
//      of this software and associated documentation files (the "Software"), to deal
//      in the Software without restriction, including without limitation the rights
//      to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//      copies of the Software, and to permit persons to whom the Software is
//      furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
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
#include "TimeStamp.h"
#include <iostream>

class BeatDetector {
public:
    //BeatDetector(int, char*);
    void LoadSong(int, char *);

    void loadSystem();

    ~BeatDetector();

    void updateTime();

    void loadNewSong(int, char *);

    float *getCurrentSpectrum();

    float calculateFluxAndSmoothing(float *);

    void update();

    FMOD_SYSTEM *fmodSetup();

    void FMODErrorCheck(FMOD_RESULT);

    void setStarted(FMOD_BOOL);

    TimeStamp *getLastBeat();

    bool isPlaying();

    char *getSongName();

    char *getArtistName();

    bool stringValid(const std::string &str);

    int getTime();

    void loadSongToDelay(int milliseconds);

    TimeStamp *getCurrentTime();

    TimeStamp *getSongLength();

    FMOD_SYSTEM *getSystem();

    float getFreq();


    //Singelton
    static BeatDetector *Instance() {
        if (instance == 0) {
            instance = new BeatDetector();
        }
        return instance;
    }

private:
    BeatDetector() { };
    static BeatDetector *instance;
    FMOD_SYSTEM *system;
    FMOD_RESULT result;
    int sampleSize;
    int test;
    int fullSeconds;
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
    TimeStamp *lastBeatRegistered;
    TimeStamp *totalSongTime;
    char songName[50];
    char *artistName;
    FMOD_TAG tag;
    TimeStamp *currentTimeStamp;

    FMOD_SOUND *audio;
    FMOD_SOUND *audio2;
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

    clock_t t1, t2;

    float hzRange;

    std::vector<float> spectrumFluxes;
    std::vector<float> smootherValues;
    float median;
    float smoothMedian;
    float beatThreshold;
    float thresholdSmoother;

    float freq;
};

#endif
