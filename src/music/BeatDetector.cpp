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

#include "BeatDetector.h"
#include "string.h"

BeatDetector *BeatDetector::instance = 0;

void BeatDetector::loadSystem() {
    system = fmodSetup();
    FMODErrorCheck(FMOD_System_CreateChannelGroup(system, NULL, &channelMusic));
    FMOD_Channel_SetChannelGroup(songChannel1, channelMusic);
}

BeatDetector::~BeatDetector() {
    delete system;
}

void BeatDetector::loadSong(int sSize, char *audioString) {
    sampleSize = sSize;
    songString = audioString;

    areWePlaying = true;
    specFlux = 0.0f;
    timeBetween = 0;
    initialTime = (int) clock();
    currentTime = 0;
    currentSeconds = 0;
    lastSeconds = 0;
    currentMillis = 0;
    currentMinutes = 0;
    median = 0.0f;
    smoothMedian = 0.0f;
    beatThreshold = 0.6f;
    thresholdSmoother = 0.6f;
    started = false;
    lastBeatRegistered = new char;
    timeToDelay = 0;
    paused = false;

    previousFFT = new float[sampleSize / 2 + 1];
    for (int i = 0; i < sampleSize / 2; i++) {
        previousFFT[i] = 0;
    }

    FMOD_Sound_GetLength(audio, &seconds, FMOD_TIMEUNIT_MS);
    FMOD_Sound_GetDefaults(audio, &sampleRate, 0, 0, 0);
    seconds = ((seconds + 500) / 1000);
    minutes = seconds / 60;
    seconds = seconds - (minutes * 60);

    FMOD_Sound_Release(audio);

    FMODErrorCheck(FMOD_System_CreateStream(system, songString, FMOD_SOFTWARE, 0, &audio));

    FMODErrorCheck(FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, audio, true, &songChannel1));

    FMOD_Channel_SetChannelGroup(songChannel1, channelMusic);
    FMOD_Channel_SetPaused(songChannel1, true);

    debug.print("loading sound:", audioString);
}

void BeatDetector::updateTime() {
    currentTime = (int) clock();
    currentTime = currentTime - initialTime;


    if (currentMinutes > 0)
        currentSeconds = ((currentTime / 1000) - (60 * currentMinutes));
    else
        currentSeconds = (currentTime / 1000);

    if (currentSeconds != lastSeconds) {
        currentMillis = 0;
        lastSeconds = currentSeconds;
    }
    else {
        currentMillis++;
    }

    currentMinutes = ((currentTime / 1000) / 60);

    if (timeToDelay != 0) {
        if (currentTime > timeToDelay) {
            FMOD_Channel_SetPaused(songChannel2, false);
            timeToDelay = 0;
        }
    }
}

float *BeatDetector::getCurrentSpectrum() {
    float *specLeft, *specRight, *tempSpec;
    specLeft = new float[sampleSize];
    specRight = new float[sampleSize];
    tempSpec = new float[sampleSize / 2 + 1];

    FMOD_Channel_GetSpectrum(songChannel1, specLeft, sampleSize, 0, FMOD_DSP_FFT_WINDOW_HAMMING);
    FMOD_Channel_GetSpectrum(songChannel1, specRight, sampleSize, 1, FMOD_DSP_FFT_WINDOW_HAMMING);

    for (int i = 0; i < sampleSize / 2; i++) {
        tempSpec[i] = (specLeft[i] + specRight[i]);
    }

    delete[] specLeft;
    delete[] specRight;

    return tempSpec;
}

float BeatDetector::calculateFluxAndSmoothing(float *currentSpectrum) {
    specFlux = 0.0;

    for (int i = 0; i < sampleSize / 2; i++) {
        difference = currentSpectrum[i] - previousFFT[i];

        if (difference > 0) {
            specFlux += difference;
        }
    }

    if (spectrumFluxes.size() > 0 && spectrumFluxes.size() < 10) {
        std::sort(spectrumFluxes.begin(), spectrumFluxes.end());
        std::sort(smootherValues.begin(), smootherValues.end());

        if (spectrumFluxes.at(spectrumFluxes.size() / 2) > 0) {
            median = spectrumFluxes.at(spectrumFluxes.size() / 2);
        }

        if (smootherValues.size() > 0 && smootherValues.size() < 5) {

            if (smootherValues.at(smootherValues.size() / 2) > 0) {
                smoothMedian = smootherValues.at(smootherValues.size() / 2);
            }
        }
    }

    for (int i = 0; i < sampleSize / 2; i++) {
        spectrumFluxes.push_back(specFlux);

        if (spectrumFluxes.size() >= 10) {
            spectrumFluxes.erase(spectrumFluxes.begin());
        }
    }

    for (int j = 0; j < sampleSize / 2; j++)
        previousFFT[j] = currentSpectrum[j];

    if (smoothMedian > 1)
        thresholdSmoother = 0.8f;
    if (smoothMedian > 2 && smoothMedian < 4)
        thresholdSmoother = 1.0f;
    if (smoothMedian > 4 && smoothMedian < 6)
        thresholdSmoother = 2.2f;
    if (smoothMedian > 6)
        thresholdSmoother = 2.4f;

    return thresholdSmoother + median;
}

void BeatDetector::update() {

    if (started) {
        float *specStereo;

        updateTime();

        specStereo = getCurrentSpectrum();

        beatThreshold = calculateFluxAndSmoothing(specStereo);

        if (specFlux > beatThreshold && (clock() - timeBetween) > 350) {
            smootherValues.push_back(specFlux);

            if (smootherValues.size() >= 5) {
                smootherValues.erase(smootherValues.begin());
            }

            timeBetween = (unsigned int) clock();

            lastBeatRegistered = new char;
            freq = specFlux;
        }
        else if ((clock() - timeBetween) > 5000) {
            if (thresholdSmoother > 0.4f)
                thresholdSmoother -= 0.4f;

            timeBetween = (unsigned int) clock();
        }

        if (!delayedSong)
            FMOD_Channel_IsPlaying(songChannel1, &areWePlaying);
        else
            FMOD_Channel_IsPlaying(songChannel2, &areWePlaying);

        delete[] specStereo;
    }
    else {
        std::cin >> test;

        if (test == 1)
            setStarted(true);
    }

}

FMOD_SYSTEM *BeatDetector::fmodSetup() {
    FMOD_SYSTEM *system;
    FMOD_RESULT result;
    unsigned int version;
    int numDrivers;
    FMOD_SPEAKERMODE speakerMode;
    FMOD_CAPS caps;
    char name[256];

    result = FMOD_System_Create(&system);
    FMODErrorCheck(result);

    result = FMOD_System_GetVersion(system, &version);
    FMODErrorCheck(result);

    result = FMOD_System_GetNumDrivers(system, &numDrivers);
    FMODErrorCheck(result);

    if (numDrivers == 0) {
        result = FMOD_System_SetOutput(system, FMOD_OUTPUTTYPE_NOSOUND);
        FMODErrorCheck(result);
    }
    else {
        result = FMOD_System_GetDriverCaps(system, 0, &caps, 0, &speakerMode);
        FMODErrorCheck(result);

        result = FMOD_System_SetSpeakerMode(system, speakerMode);
        FMODErrorCheck(result);

        if (caps & FMOD_CAPS_HARDWARE_EMULATED) {
            result = FMOD_System_SetDSPBufferSize(system, 1024, 10);
            FMODErrorCheck(result);
        }
        result = FMOD_System_GetDriverInfo(system, 0, name, 256, 0);
        FMODErrorCheck(result);

        if (strstr(name, "SigmaTel")) {
            result = FMOD_System_SetSoftwareFormat(system, 48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0,
                                                   FMOD_DSP_RESAMPLER_LINEAR);
            FMODErrorCheck(result);
        }
    }

    result = FMOD_System_Init(system, 100, FMOD_INIT_NORMAL, 0);

    if (result == FMOD_ERR_OUTPUT_CREATEBUFFER) {
        result = FMOD_System_SetSpeakerMode(system, FMOD_SPEAKERMODE_STEREO);
        FMODErrorCheck(result);
        result = FMOD_System_Init(system, 100, FMOD_INIT_NORMAL, 0);
    }

    FMODErrorCheck(result);

    return system;
}

void BeatDetector::FMODErrorCheck(FMOD_RESULT result) {
    if (result != FMOD_OK) {
        debug.print("FMOD ERROR:", result, FMOD_ErrorString(result));
        exit(-1);
    }
}

void BeatDetector::setStarted(FMOD_BOOL areWeStarted) {
    started = areWeStarted;

    FMOD_Channel_SetPaused(songChannel1, !started);
}

char *BeatDetector::getLastBeat() {
    return lastBeatRegistered;
}

bool BeatDetector::isPlaying() {
    return (bool) areWePlaying;
}

float BeatDetector::getFreq() {
    return freq;
}

void BeatDetector::setPaused(FMOD_BOOL pause) {
    FMOD_Channel_SetPaused(songChannel1,pause);
}






