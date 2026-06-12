#pragma once

#include "SFML/Graphics.hpp"
#include "State.h"
#include "Game.h"
#include "Obj.h"

namespace RawEngine {
    class OptionState : public State
    {
        public:
            OptionState(EngineDataRef eData) : eData(eData) {};
            virtual ~OptionState() {};
            void init();
            void update(float deltaT);
            void draw(float deltaT);
        private :
            void ifKeyPressedEvent (sf::Event &ev);
            void ifKeyReleasedEvent (sf::Event &ev);
            void ifMousePressed (sf::Event &ev);
            void ifMouseReleased (sf::Event &ev);
        private:
            EngineDataRef eData;
            sf::Clock clock;
    };
}
