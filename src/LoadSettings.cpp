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

#include "LoadSettings.h"

std::shared_ptr<sf::RenderWindow> LoadSettings::set() {
    // read();

    // if (resX == 0 || resY == 0 || bit == 0) {
    //	 setDefault();
    // }

    resX = 1000;
    resY = 900;
    bit = 32;

    std::shared_ptr<sf::RenderWindow> initWindow(
            new sf::RenderWindow(sf::VideoMode(resX, resY, bit), "Squarly Hoop", sf::Style::Default));

    initWindow->setVerticalSyncEnabled(vsync);

    return initWindow;
}

ifstream readFromFile("settings");

void LoadSettings::read() {
    string line;

    readFromFile >> line;
    if (line == "resolution") {
        readFromFile >> resX >> resY >> bit;
    }

    readFromFile >> line;
    if (line == "vsync") {
        string value;
        readFromFile >> value;

        vsync = value == "true";
    }

    readFromFile >> line;
    if (line == "antialiasing") {
        readFromFile >> AA;
    }

    readFromFile >> line;
    if (line == "window_mode") {
        readFromFile >> windowMode;
    }
}

void LoadSettings::setDefault() {
    ofstream writeToFile("settings");
    writeToFile << "resolution 800 600 32" << endl << "vsync true" << endl << "antialiasing 0" << endl <<
    "window_mode fullscreen";

    read();
}
