#include "E_P_Soldier.h"

namespace RawEngine{
    E_P_Soldier::E_P_Soldier(EngineDataRef eData, GameDataRef gameData) {
        this->eData = eData;
        this->gData = gameData;

        GD_ASSETS.loadFromSpriteSheet(this->mainSp,"E_UNITS",0,0,25,25);
        this->id = GameObjID::E_P_SOLDIER;

        this->health = 10;
        this->solid = true;
    }
    void E_P_Soldier::update (float deltaT) {
        checkIfDefaultColorsSet();
        if(this->selected){
            if(!this->moving){
                popUpAndDisappearAnim(deltaT);
            }
        }
        if(this->moveNext != sf::Vector2f(0,0) && this->selected){
            updateMovement();
        }
    }
    void E_P_Soldier::draw (float deltaT) {
        GD_WIN.draw(this->mainSp);
    }
    bool E_P_Soldier::ifKeyPressedEvent(sf::Event& ev) {
        numpadControls(ev);
        return false;
    }

    bool E_P_Soldier::ifKeyReleasedEvent(sf::Event& ev) {
        return false;
    }

    bool E_P_Soldier::ifMousePressed(sf::Event& ev) {
        return false;
    }

    bool E_P_Soldier::ifMouseReleased(sf::Event& ev) {
        return false;
    }
}
