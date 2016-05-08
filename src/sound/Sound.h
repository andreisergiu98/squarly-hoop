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

#ifndef SFMLGAME_SOUND_H
#define SFMLGAME_SOUND_H

#include "fmodex/fmod.hpp"
#include "fmodex/fmod_errors.h"
#include "../DebugHelper.h"

class Sound {
public:
    Sound();
    ~Sound();

    void play();

    void pause();

    void resume();

    void setLooped(bool looped);

    void setVolume(float volume);

    void loadSound(std::string location);

private:
    FMOD_SYSTEM *system;
    FMOD_SOUND *audio;
    FMOD_CHANNELGROUP *channelGroup;
    FMOD_CHANNEL *channel;

    float volume;

    std::string location;

    void load();

    bool loaded;

    FMOD_MODE mode;

    FMOD_SYSTEM *fmodSetup();
    void FMODErrorCheck(FMOD_RESULT result);
};


#endif //SFMLGAME_SOUND_H
