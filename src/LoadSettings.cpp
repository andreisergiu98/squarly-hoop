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
    if (!std::ifstream("settings")) {
        debug.print("settings not found", "");
        setDefault();
    }

    read();

    if (windowMode == "fullscreen") {
        std::shared_ptr<sf::RenderWindow> initWindow(
                new sf::RenderWindow(res, "Squarly Hoop", sf::Style::Fullscreen, contextSettings));
        initWindow->setVerticalSyncEnabled(vsync);

        return initWindow;
    }
    if (windowMode == "windowed") {
        std::shared_ptr<sf::RenderWindow> initWindow(
                new sf::RenderWindow(res, "Squarly Hoop", sf::Style::Close, contextSettings));
        initWindow->setVerticalSyncEnabled(vsync);

        return initWindow;
    }

    std::shared_ptr<sf::RenderWindow> initWindow(
            new sf::RenderWindow(res, "Squarly Hoop", sf::Style::Titlebar, contextSettings));
    initWindow->setVerticalSyncEnabled(vsync);

    return initWindow;

}

ifstream readFromFile("settings");

void LoadSettings::read() {

    debug.print("loading settings", "");

    while (!readFromFile.eof()) {
        string line;

        readFromFile >> line;
        if (line == "resolution") {
            readFromFile >> res.width >> res.height;
            debug.print("set", line, res.width, res.height);
        }
        else if (line == "windowmode") {
            readFromFile >> windowMode;
            debug.print("set", line, windowMode);
        }
        else if (line == "vsync") {
            string value;
            readFromFile >> value;
            vsync = value == "true";
            debug.print("set", line, vsync);
        }
        else if (line == "antialiasing") {
            readFromFile >> contextSettings.antialiasingLevel;
            debug.print("set", line, contextSettings.antialiasingLevel);
        }
        else if (line == "depthbits") {
            readFromFile >> contextSettings.depthBits;
            debug.print("set", line, contextSettings.depthBits);
        }
        else if (line == "stencilbits") {
            readFromFile >> contextSettings.stencilBits;
            debug.print("set", line, contextSettings.stencilBits);
        }
        else if (line == "openGLmajorVersion") {
            readFromFile >> contextSettings.majorVersion;
            debug.print("set", line, contextSettings.majorVersion);
        }
        else if (line == "openGLminorVersion") {
            readFromFile >> contextSettings.minorVersion;
            debug.print("set", line, contextSettings.minorVersion);
        }
    }

    debug.print("settings loaded", "");
}

void LoadSettings::setDefault() {
    debug.print("loading default settings", "");

    ofstream writeToFile("settings");

    writeToFile << "resolution 1000 900\n"
            "windowmode fullscreen\n"
            "vsync true\n"
            "antialiasing 8\n"
            "depthbits 24\n"
            "stencilbits 8\n"
            "openGLmajorVersion 4\n"
            "openGLminorVersion 5";

}

LoadSettings::LoadSettings() {
    res = sf::VideoMode(1000, 900, 32);
    contextSettings.depthBits = 24;
    contextSettings.stencilBits = 8;
    contextSettings.antialiasingLevel = 8;
}


