#pragma once

#include "GameObj.h"
#include "game/GameData.h"

namespace RawEngine {
    class T_Default : public GameObj
    {
        public:
            T_Default(EngineDataRef eData, GameDataRef gameData);
            ~T_Default() {
//                printf("delete T_DEFAULT\n");
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
            GameDataRef gameData;
            sf::Clock clock;
    };
}
