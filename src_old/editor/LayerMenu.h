#pragma once

#include "Game.h"
#include "Obj.h"
#include "LevelHandler.h"
#include "EditorState.h"

namespace RawEngine {

    class LayerButton;
    typedef std::vector<std::shared_ptr<LayerButton>> LayBtnCont;

    /////////////////////LAYER MENU//////////////////

    class LayerMenu : public Obj
    {
        public:
            LayerMenu(EditorDataRef editData,EngineDataRef eData);
            ~LayerMenu() {printf("Kill LayerMenu\n");}
            void init ();
            void update (float deltaT);
            void draw (float deltaT);
            bool ifKeyPressedEvent (sf::Event &ev);
            bool ifKeyReleasedEvent (sf::Event &ev);
            bool ifMousePressed (sf::Event &ev);
            void nextWithMouse (int index, LayBtnCont& menObjSt);
            bool ifMouseReleased (sf::Event &ev);

            bool objectHoveredOver(sf::Vector2i mousePos) {return false;}

        public :
            LayBtnCont layerCont;
        private:
            EngineDataRef eData;
            EditorDataRef editData;

            sf::Sprite menu;
            sf::Vector2u menuSize;
    };

    /////////////////LAYER BUTTON///////////////////

    class LayerButton : public Obj
    {
        public:
            LayerButton(EditorDataRef editData, EngineDataRef eData, std::string dispText,
                float x, float y, float scaleX, float scaleY, float rot, sf::Color color, Layer* layer);
            virtual ~LayerButton() {printf("Destroy %s\n",this->name.c_str());}
            void changeEye ();
            void loadTextures();
            bool objectHoveredOver (sf::Vector2i mousePos);
            void update (float deltaT);
            void draw (float deltaT);
            bool ifKeyPressedEvent (sf::Event &ev);
            bool ifKeyReleasedEvent (sf::Event &ev);
            bool ifMousePressed (sf::Event &ev);
            bool ifMouseReleased (sf::Event &ev);

        public :
            Layer* layer;
            bool eyeOpen = true;
            sf::Sprite sprite;
            sf::Sprite eye;
            sf::Text displayName;
        private :
            EngineDataRef eData;
            EditorDataRef editData;
    };
}
