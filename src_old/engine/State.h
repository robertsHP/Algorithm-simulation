#pragma once

#include "Obj.h"
#include <memory>
#include <map>

namespace RawEngine {
    class State {
        public :
            virtual ~State () {}
            virtual void init() = 0;
            virtual void update (float deltaT) = 0;
            virtual void draw (float deltaT) = 0;

            virtual void ifKeyPressedEvent (sf::Event &ev) = 0;
            virtual void ifKeyReleasedEvent (sf::Event &ev) = 0;
            virtual void ifMousePressed(sf::Event& ev) = 0;
            virtual void ifMouseReleased(sf::Event& ev) = 0;

            virtual void pause () {}
            virtual void resume () {}

        public:
            ObjSt menObj;
    };
}
