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

#include <cstring>
#include "Sound.h"

Sound::Sound() {
    system = fmodSetup();
    FMODErrorCheck(FMOD_System_CreateChannelGroup(system, NULL, &channelGroup));
    FMOD_Channel_SetChannelGroup(channel, channelGroup);
    loaded = false;
    volume = 1.f;
    mode = FMOD_LOOP_OFF;
}

void Sound::FMODErrorCheck(FMOD_RESULT result) {
    if (result != FMOD_OK) {
        debug::print("FMOD ERROR:", result, FMOD_ErrorString(result));
        exit(-1);
    }
}

void Sound::play() {
    load();
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, audio, false, &channel);
    FMOD_Channel_SetVolume(channel, volume);
    FMOD_Channel_SetMode(channel, mode);
}

void Sound::load() {
    if (loaded) {
        FMOD_Sound_Release(audio);
    }
    char *path = &location[0u];
    FMOD_System_CreateSound(system, path, FMOD_SOFTWARE, 0, &audio);
    FMOD_Channel_SetChannelGroup(channel, channelGroup);
    FMOD_Channel_SetPaused(channel, true);
    loaded = true;
}


void Sound::pause() {
    FMOD_Channel_SetPaused(channel, true);
}

void Sound::loadSound(string location) {
    this->location = location;
}

void Sound::resume() {
    FMOD_Channel_SetPaused(channel, false);
}

void Sound::setVolume(float volume) {
    FMOD_Channel_SetVolume(channel, volume);
    this->volume = volume;
}

void Sound::setLooped(bool looped) {
    if(looped){
        mode = FMOD_LOOP_NORMAL;
    }
    if(!looped){
        mode = FMOD_LOOP_OFF;
    }
    FMOD_Channel_SetMode(channel, mode);
}

Sound::~Sound() {
    FMOD_System_Release(system);
    FMOD_Sound_Release(audio);
    FMOD_ChannelGroup_Release(channelGroup);
}

FMOD_SYSTEM *Sound::fmodSetup() {
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

















