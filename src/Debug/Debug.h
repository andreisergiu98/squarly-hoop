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
#ifndef SFMLGAME_DEBUG_H
#define SFMLGAME_DEBUG_H

#include <iostream>
#include <fstream>

class Debug {
public:
    template<typename T>
    void print(T message);

    template<typename T, typename... Args>
    void print(T first, Args... args);

    void clear();

    void clear_log();

private:
    template<typename T>
    void log(T message);
};

#include "Debug.inl"

#endif //SFMLGAME_DEBUG_H


