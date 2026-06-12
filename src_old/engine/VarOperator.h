#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <cstring>

namespace VarOp {
    std::string resAsString (sf::VideoMode& mode);
    std::string booltoString (bool b);

    std::vector<std::string> split (std::string& str, std::string symb);

    unsigned int uintFstr (unsigned int start, unsigned int fin, std::string line);

    sf::VideoMode getResType (std::string vm, unsigned int bpp, std::vector<sf::VideoMode>& modes);
}
