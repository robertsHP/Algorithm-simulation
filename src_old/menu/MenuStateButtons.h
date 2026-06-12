#pragma once

#include "Obj.h"
#include "Game.h"

///Button order in the code should be the same as ingame.

namespace RawEngine {

    //////////RESUME BUTTON/////////////////////

    class ResumeButton : public Obj
    {
        public:
            ResumeButton(EngineDataRef data, float x, float y, float scaleX, float scaleY, float rot);
            virtual ~ResumeButton() {printf("Destroy %s\n",this->name.c_str());}
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

    //////////GAME STATE BUTTON//////////////

    class GameButton : public Obj
    {
        public:
            GameButton(EngineDataRef data, float x, float y, float scaleX, float scaleY, float rot);
            virtual ~GameButton() {printf("Destroy %s\n",this->name.c_str());}
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

    //////////EDITOR STATE BUTTON//////////////

    class EditorButton : public Obj
    {
        public:
            EditorButton(EngineDataRef data, float x, float y, float scaleX, float scaleY, float rot);
            virtual ~EditorButton() {printf("Destroy %s\n",this->name.c_str());}
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

    /////////OPTION STATE BUTTON//////

    class OptionButton : public Obj
    {
        public:
            OptionButton(EngineDataRef data, float x, float y, float scaleX, float scaleY, float rot);
            virtual ~OptionButton() {printf("Destroy %s\n",this->name.c_str());}

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

    ////////EXIT BUTTON//////////

    class ExitButton : public Obj
    {
        public:
            ExitButton(EngineDataRef data, float x, float y, float scaleX, float scaleY, float rot);
            virtual ~ExitButton() {printf("Destroy %s\n",this->name.c_str());}
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
