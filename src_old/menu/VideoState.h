#pragma once

#include "SFML/Graphics.hpp"
#include "State.h"
#include "Game.h"
#include "Config.h"
#include "Obj.h"

namespace RawEngine {
    class VideoState : public State
    {
        public:
            VideoState(EngineDataRef eData) : eData(eData) {};
            virtual ~VideoState() {};
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
