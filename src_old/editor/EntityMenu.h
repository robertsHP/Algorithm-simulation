#pragma once

#include "Game.h"
#include "Obj.h"
#include "LevelHandler.h"
#include "EditorState.h"

namespace RawEngine {
    class EntityMenu : public Obj
    {
        public:
            EntityMenu(EditorDataRef editData, EngineDataRef eData);
            ~EntityMenu() {printf("Kill EntityMenu\n");}
            void init ();
            void update (float deltaT);
            void draw (float deltaT);
            bool ifKeyPressedEvent (sf::Event &ev);
            bool ifKeyReleasedEvent (sf::Event &ev);
            bool ifMousePressed (sf::Event &ev);
            bool ifMouseReleased (sf::Event &ev);

            bool objectHoveredOver(sf::Vector2i mousePos) {return false;}

            void setSelTilePos();
            void loadTileMenuTiles ();

            bool getActPerf () {return this->actionPerformed;}
            void setActPerf (bool cond) {this->actionPerformed = cond;}
        private:
            EngineDataRef eData;
            EditorDataRef editData;

            Layer entMObjs;
            unsigned int selObj = 0;
            bool actionPerformed = false;

            sf::Sprite up;
            sf::Sprite menu;
            sf::Sprite down;

            sf::Vector2u upSize;
            sf::Vector2u menuSize;
            sf::Vector2u downSize;
            sf::Vector2u selSize;
    };
}
