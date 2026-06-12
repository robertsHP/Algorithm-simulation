#include "E_P_Tank.h"

namespace RawEngine{
    E_P_Tank::E_P_Tank(EngineDataRef data) : _data(data) {
        GD_ASSETS.loadFromSpriteSheet(this->_mainSp,"E_UNITS",3,0,25,25);
        this->_id = GameObjID::E_P_TANK;
    };
    E_P_Tank::E_P_Tank(EngineDataRef data, float x, float y, float scale) : _data(data)
    {
        GD_ASSETS.loadFromSpriteSheet(this->_mainSp,"E_UNITS",3,0,25,25);

        this->_id = GameObjID::E_P_TANK;
        this->_mainSp.setPosition(x*scale,y*scale);
        this->_mainSp.setScale(scale,scale);
    }
    void E_P_Tank::update (float deltaT) {

    }
    void E_P_Tank::draw (float deltaT) {
        GD_WIN.draw(this->_mainSp);
    }
    bool E_P_Tank::ifKeyPressedEvent(sf::Event& ev) {
        return false;
    }

    bool E_P_Tank::ifKeyReleasedEvent(sf::Event& ev) {
        return false;
    }

    bool E_P_Tank::ifMousePressed(sf::Event& ev) {
        return false;
    }

    bool E_P_Tank::ifMouseReleased(sf::Event& ev) {
        return false;
    }
}
