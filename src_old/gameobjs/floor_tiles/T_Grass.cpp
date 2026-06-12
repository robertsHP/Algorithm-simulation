#include "T_Grass.h"

namespace RawEngine{
    T_Grass::T_Grass(EngineDataRef eData, GameDataRef gameData) {
        this->eData = eData;
        this->gameData = gameData;
        GD_ASSETS.loadFromSpriteSheet(this->mainSp,"T_GROUND",1,0,25,25);
        this->id = GameObjID::T_GRASSNORMAL;
    }
    void T_Grass::update (float deltaT) {

    }
    void T_Grass::draw (float deltaT) {
        GD_WIN.draw(this->mainSp);
    }
    bool T_Grass::ifKeyPressedEvent(sf::Event& ev)
    {
        return false;
    }
    bool T_Grass::ifKeyReleasedEvent(sf::Event& ev)
    {
        return false;
    }
    bool T_Grass::ifMousePressed(sf::Event& ev)
    {
        return false;
    }
    bool T_Grass::ifMouseReleased(sf::Event& ev)
    {
        return false;
    }
}
