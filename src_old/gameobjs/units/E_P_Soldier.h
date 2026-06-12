#pragma once

#include "GameObj.h"
#include "game/GameData.h"

namespace RawEngine {

    class E_P_Soldier : public GameObj
    {
        public:
            E_P_Soldier(EngineDataRef eData, GameDataRef gameData);
            ~E_P_Soldier() {
//                printf("delete entity Soldier\n");
            }
            void draw(float deltaT);
            void update(float deltaT);

            bool objectHoveredOver(sf::Vector2i mousePos) {return false;}

            bool ifKeyPressedEvent (sf::Event &ev);
            bool ifKeyReleasedEvent (sf::Event &ev);
            bool ifMousePressed (sf::Event &ev);
            bool ifMouseReleased (sf::Event &ev);
        protected :
            EngineDataRef eData;
            GameDataRef gData;
    };
}
