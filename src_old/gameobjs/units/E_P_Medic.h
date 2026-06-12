#pragma once

#include "Obj.h"
#include "Game.h"

namespace RawEngine {
    class E_P_Medic : public Obj
    {
        public:
            E_P_Medic(EngineDataRef data);
            E_P_Medic(EngineDataRef data, float x, float y, float scale);
            ~E_P_Medic() {
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
            EngineDataRef _data;
    };
}
