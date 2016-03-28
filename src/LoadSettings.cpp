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
#include "Utils.h"


std::shared_ptr<sf::RenderWindow> LoadSettings::load() {
    Debug::print("loading settings", "");

    if (!std::ifstream("settings")) {
        Debug::print("settings not found", "");
        setDefault();
    }

    ifstream readFromFile("settings");

    while (!readFromFile.eof()) {
        string line;

        readFromFile >> line;
        if (line == "resolution") {
            readFromFile >> res.width >> res.height;
            Debug::print("set", line, res.width, res.height);
        }
        else if (line == "windowmode") {
            readFromFile >> windowMode;
            Debug::print("set", line, windowMode);
        }
        else if (line == "vsync") {
            string value;
            readFromFile >> value;
            vsync = value == "true";
            Debug::print("set", line, value);
        }
        else if (line == "smoothtextures") {
            string value;
            readFromFile >> value;
            smooth = value == "true";
            Debug::print("set", line, value);
        }
        else if (line == "antialiasing") {
            readFromFile >> contextSettings.antialiasingLevel;
            Debug::print("set", line, contextSettings.antialiasingLevel);
        }
        else if (line == "depthbits") {
            readFromFile >> contextSettings.depthBits;
            Debug::print("set", line, contextSettings.depthBits);
        }
        else if (line == "stencilbits") {
            readFromFile >> contextSettings.stencilBits;
            Debug::print("set", line, contextSettings.stencilBits);
        }
        else if (line == "openGL") {
            readFromFile >> contextSettings.majorVersion >> contextSettings.minorVersion;
            Debug::print("set", line, contextSettings.majorVersion);
            Debug::print("set", line, contextSettings.minorVersion);
        }
    }
    readFromFile.close();

    Debug::print("settings loaded", "");

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
    if (windowMode == "none") {
        std::shared_ptr<sf::RenderWindow> initWindow(
                new sf::RenderWindow(res, "Squarly Hoop", sf::Style::None, contextSettings));
        initWindow->setVerticalSyncEnabled(vsync);

        return initWindow;
    }

    std::shared_ptr<sf::RenderWindow> initWindow(
            new sf::RenderWindow(res, "Squarly Hoop", sf::Style::Default, contextSettings));
    initWindow->setVerticalSyncEnabled(vsync);

    return initWindow;

}

void LoadSettings::setDefault() {
    Debug::print("loading default settings", "");

    ofstream writeToFile("settings");

    writeToFile << "resolution 1000 900\n"
            "windowmode windowed\n"
            "vsync true\n"
            "smoothtextures true\n"
            "antialiasing 8\n"
            "depthbits 24\n"
            "stencilbits 8\n"
            "openGL 4 5\n";

    writeToFile.close();
}

LoadSettings::LoadSettings() {
    res = sf::VideoMode(1000, 900, 32);
    contextSettings.depthBits = 24;
    contextSettings.stencilBits = 8;
    contextSettings.antialiasingLevel = 8;
    smooth = true;
}

bool LoadSettings::smoothTextures() {
    return smooth;
}


