#include "VarOperator.h"

namespace VarOp {
    std::string resAsString (sf::VideoMode& mode) {
        return std::to_string(mode.width)+"x"+std::to_string(mode.height);
    }
    std::string booltoString (bool b) {
        return (b) ? "true" : "false";
    }
    std::vector<std::string> split (std::string& str, std::string symb) {
        std::vector<std::string> splitCont;

        auto start = 0U;
        auto ending = str.find(symb);
        std::size_t i = 0;
        while (ending != std::string::npos) {
            splitCont.push_back(str.substr(start, ending - start));
            start = ending + symb.length();
            ending = str.find(symb, start);
            ++i;
        }
        return splitCont;
    }
    unsigned int uintFstr (unsigned int start, unsigned int fin, std::string line) {
        std::string numStr = line.substr(start, fin);
        std::stringstream numStream (numStr);
        unsigned int num = 0;
        numStream >> num;
        return num;
    }
    sf::VideoMode getResType (std::string resN, unsigned int bpp, std::vector<sf::VideoMode>& modes) {
        std::string   curName;
        sf::VideoMode mode;
        sf::VideoMode finalVM;
        std::size_t   i;

        for (i = 0; i < modes.size(); ++i) {
            mode = modes[i];
            curName = VarOp::resAsString(mode);

            bool condApply   = curName == resN && bpp == mode.bitsPerPixel;
            bool outOfBounds = i == modes.size()-1;

            if(condApply || outOfBounds){
                return mode;
            }
        }
        finalVM = modes[modes.size()];
        return finalVM;
    }
}
