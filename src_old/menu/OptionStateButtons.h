#pragma once

#include "Obj.h"
#include "Game.h"

///Button order in the code should be the same as ingame.

namespace RawEngine {
    ///////VIDEO STATE BUTTON////////
    class VideoButton : public Obj
    {
        public:
            VideoButton(EngineDataRef data, float x, float y, float scaleX, float scaleY, float rot);
            virtual ~VideoButton() {printf("Destroy %s\n",this->name.c_str());}

            bool objectHoveredOver (sf::Vector2i mousePos);
            void loadTextures();
            void update (float deltaT);
            void draw (float deltaT);
            bool ifKeyPressedEvent (sf::Event &ev);
            bool ifKeyReleasedEvent (sf::Event &ev);
            bool ifMousePressed (sf::Event &ev);
            bool ifMouseReleased (sf::Event &ev);
        private :
            sf::Sprite sprite;
            EngineDataRef eData;
    };

    ////////OPTION EXIT BUTTON//////////

    class OptionExitButton : public Obj
    {
        public:
            OptionExitButton(EngineDataRef data, float x, float y, float scaleX, float scaleY, float rot);
            virtual ~OptionExitButton() {printf("Destroy %s\n",this->name.c_str());}
            void loadTextures();
            bool objectHoveredOver (sf::Vector2i mousePos);
            void update (float deltaT);
            void draw (float deltaT);
            bool ifKeyPressedEvent (sf::Event &ev);
            bool ifKeyReleasedEvent (sf::Event &ev);
            bool ifMousePressed (sf::Event &ev);
            bool ifMouseReleased (sf::Event &ev);
        private :
            sf::Sprite sprite;
            EngineDataRef eData;
    };
}
