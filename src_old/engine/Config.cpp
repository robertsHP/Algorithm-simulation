#include "Config.h"
#include "VarOperator.h"
#include "OSChecker.h"

#define stringify( name ) # name

namespace RawEngine {

    void Config::readCFile() {
        std::string name, value, fin;

        std::ifstream cFile("config.ini");
        if (cFile.is_open()) {
            std::string line;
            while(getline(cFile, line)){
                line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
                if(line.find('[') == std::string::npos && line.find(']') == std::string::npos && line.length() != 0){
                    auto delimiterPos = line.find("=");
                    name = line.substr(0, delimiterPos);
                    value = line.substr(delimiterPos + 1);
                    this->_info[name] = value;
                    fin = name+" "+value;
                    printf("%s\n",fin.c_str());
                }
            }
            cFile.close();
            infoToValues();
        } else printf("Couldn't open config file for reading.\n");
    }
    void Config::changeLine (std::string& line) {
        auto delimiterPos = line.find("=");
        std::string name = line.substr(0, delimiterPos);
        std::string value = line.substr(delimiterPos + 1);
        if(this->_info[name] != value){
            line = name+"="+this->_info[name];
        }
    }
    void Config::writeToCFile() {
        try {
            valuesToInfo();
            std::ifstream cFile("config.ini");
            std::ofstream newCFile("configNew.ini");
            if (cFile.is_open() && newCFile.is_open()) {
                std::string line;
                while(getline(cFile, line)){
                    if(line.find('[') == std::string::npos && line.find(']') == std::string::npos && line.length() != 0){
                        changeLine(line);
                    }
                    newCFile << line << std::endl;
                }
                cFile.close();
                newCFile.close();
                if(OS_REMOVE("config.ini") != 0)
                    throw "Failed to remove original file.";
                if(OS_RENAME("configNew.ini","config.ini") != 0)
                    throw "Failed to rename file.";
            } else throw "Couldn't open config file for writing.";
        } catch (char* exc) {
            printf("%s\n",exc);
        }
    }

    void Config::infoToValues(){
        using namespace std;

        _cst->title = this->_info["str_game_title"];
        _cst->bpp   = stoi(this->_info["int_bitsperpixel"]);
        _cst->res   = VarOp::getResType(
            this->_info["str_resolution"],
            this->_cst->bpp,
            modes
        );
        istringstream(this->_info["bol_fullscreen"]) >> boolalpha >> this->_cst->fullScr;
    }
    void Config::valuesToInfo () {
        this->_info["str_game_title"]   = _cst->title;
        this->_info["int_bitsperpixel"] = std::to_string(_cst->bpp);
        this->_info["str_resolution"]   = VarOp::resAsString(_cst->res);
        this->_info["bol_fullscreen"]   = VarOp::booltoString(_cst->fullScr);
    }

    sf::Keyboard::Key checkKeyType(std::string keyName) {
        for(sf::Keyboard::Key i = sf::Keyboard::A; i != sf::Keyboard::Return; i = (sf::Keyboard::Key)(i+1)) {
            if(stringify(i) == keyName) return i;
        }
        return sf::Keyboard::Unknown;
    }
    sf::Mouse::Button checkMouseType(std::string buttonName) {
        for(sf::Mouse::Button i=sf::Mouse::Left; i!=sf::Mouse::ButtonCount; i=(sf::Mouse::Button)(i+1)) {
            if(stringify(i) == buttonName) return i;
        }
        return sf::Mouse::ButtonCount;
    }
}
