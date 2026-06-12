#include "T_Default.h"

namespace RawEngine{
    T_Default::T_Default(EngineDataRef eData, GameDataRef gameData) {
        this->eData = eData;
        this->gameData = gameData;
        GD_ASSETS.loadFromSpriteSheet(this->mainSp, "T_GROUND",0,0,25,25);
        this->id = GameObjID::T_DEFAULT;
    }
    void T_Default::update (float deltaT) {

    }
    void T_Default::draw (float deltaT) {
        GD_WIN.draw(this->mainSp);
    }
    bool T_Default::ifKeyPressedEvent(sf::Event& ev) {
        return false;
    }

    bool T_Default::ifKeyReleasedEvent(sf::Event& ev) {
        return false;
    }

    bool T_Default::ifMousePressed(sf::Event& ev) {
        return false;
    }

    bool T_Default::ifMouseReleased(sf::Event& ev) {
        return false;
    }
}
