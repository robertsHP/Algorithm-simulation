#include "E_P_Sapper.h"

namespace RawEngine{
    E_P_Sapper::E_P_Sapper(EngineDataRef data) : _data(data) {
        GD_ASSETS.loadFromSpriteSheet(this->_mainSp,"E_UNITS",1,0,25,25);
        this->_id = GameObjID::E_P_SAPPER;
    };
    E_P_Sapper::E_P_Sapper(EngineDataRef data, float x, float y, float scale) : _data(data)
    {
        GD_ASSETS.loadFromSpriteSheet(this->_mainSp,"E_UNITS",1,0,25,25);

        this->_id = GameObjID::E_P_SAPPER;
        this->_mainSp.setPosition(x*scale,y*scale);
        this->_mainSp.setScale(scale,scale);
    }
    void E_P_Sapper::update (float deltaT) {

    }
    void E_P_Sapper::draw (float deltaT) {
        GD_WIN.draw(this->_mainSp);
    }
    bool E_P_Sapper::ifKeyPressedEvent(sf::Event& ev) {
        return false;
    }

    bool E_P_Sapper::ifKeyReleasedEvent(sf::Event& ev) {
        return false;
    }

    bool E_P_Sapper::ifMousePressed(sf::Event& ev) {
        return false;
    }

    bool E_P_Sapper::ifMouseReleased(sf::Event& ev) {
        return false;
    }
}
