#pragma once

#include "SFML/Graphics.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <map>


namespace RawEngine {

    struct ConfigStorage;

    typedef std::shared_ptr<ConfigStorage> ConfSt;
    typedef std::vector<sf::VideoMode> VCont;

    struct ConfigStorage {
        std::string title;
        unsigned int bpp;
        sf::VideoMode res;
        bool fullScr;
        float rot;
    };

    class Config {
        public :
            void readCFile();
            void changeLine (std::string& line);
            void writeToCFile();

            void infoToValues();
            void valuesToInfo();

            sf::Keyboard::Key checkKeyType (std::string keyName);
            sf::Mouse::Button checkMouseType (std::string buttonName);

        public :
            ConfSt _cst = std::make_shared<ConfigStorage>();
            std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
        private:
            std::map<std::string,std::string> _info;
    };
}
