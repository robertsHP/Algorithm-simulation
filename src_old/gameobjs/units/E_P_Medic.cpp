#include "E_P_Medic.h"

namespace RawEngine{
    E_P_Medic::E_P_Medic(EngineDataRef data) : _data(data) {
        GD_ASSETS.loadFromSpriteSheet(this->_mainSp,"E_UNITS",2,0,25,25);
        this->_id = GameObjID::E_P_MEDIC;
    };
    E_P_Medic::E_P_Medic(EngineDataRef data, float x, float y, float scale) : _data(data)
    {
        GD_ASSETS.loadFromSpriteSheet(this->_mainSp,"E_UNITS",2,0,25,25);

        this->_id = GameObjID::E_P_MEDIC;
        this->_mainSp.setPosition(x*scale,y*scale);
        this->_mainSp.setScale(scale,scale);
    }
    void E_P_Medic::update (float deltaT) {

    }
    void E_P_Medic::draw (float deltaT) {
        GD_WIN.draw(this->_mainSp);
    }
    bool E_P_Medic::ifKeyPressedEvent(sf::Event& ev) {
        return false;
    }

    bool E_P_Medic::ifKeyReleasedEvent(sf::Event& ev) {
        return false;
    }

    bool E_P_Medic::ifMousePressed(sf::Event& ev) {
        return false;
    }

    bool E_P_Medic::ifMouseReleased(sf::Event& ev) {
        return false;
    }
}
