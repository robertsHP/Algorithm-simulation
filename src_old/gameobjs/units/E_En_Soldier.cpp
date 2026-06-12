#include "E_En_Soldier.h"

namespace RawEngine{
    E_En_Soldier::E_En_Soldier(EngineDataRef data) : _data(data) {
        GD_ASSETS.loadFromSpriteSheet(this->_mainSp,"E_UNITS",0,0,25,25);
        this->_id = GameObjID::E_EN_SOLDIER;
    };
    E_En_Soldier::E_En_Soldier(EngineDataRef data, float x, float y, float scale) : _data(data)
    {
        GD_ASSETS.loadFromSpriteSheet(this->_mainSp,"E_UNITS",0,0,25,25);

        this->_id = GameObjID::E_EN_SOLDIER;
        this->_mainSp.setPosition(x*scale,y*scale);
        this->_mainSp.setScale(scale,scale);
    }
    void E_En_Soldier::update (float deltaT) {

    }
    void E_En_Soldier::draw (float deltaT) {
        GD_WIN.draw(this->_mainSp);
    }
    bool E_En_Soldier::ifKeyPressedEvent(sf::Event& ev) {
        return false;
    }

    bool E_En_Soldier::ifKeyReleasedEvent(sf::Event& ev) {
        return false;
    }

    bool E_En_Soldier::ifMousePressed(sf::Event& ev) {
        return false;
    }

    bool E_En_Soldier::ifMouseReleased(sf::Event& ev) {
        return false;
    }
}
