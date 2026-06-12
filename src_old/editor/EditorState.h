#pragma once

#include "SFML/Graphics.hpp"

#include "State.h"
#include "LevelHandler.h"
#include "ObjectHandler.h"

namespace RawEngine {

    struct EditorData;
    class EditorState;
    typedef std::shared_ptr<EditorData> EditorDataRef;

    struct EditorData {
        ///LEVEL GRID
        std::vector<Layer> layers;
        std::size_t  selLayer = 0; //selected layer which gets edited using the left or right mouse button
        sf::Vector2f changePos; //changes position of all tiles when moving the screen
        bool         drawGrid; //if true game objects with the ID T_DEFAULT get drawn

        ///OTHER LEVEL INFO
        std::string lvlName;

        ///SELECTED TILE INFO
        GameObjID  selID = GameObjID::T_DEFAULT;
        ObjPtr     selObj;
        sf::Sprite sel; //the menu sprite behind the object

        ///STATE MENU OBJECTS
        ObjStUNIQUE  mObjCont; //all menu objects like entity menu, layer menu, etc.

        ///DRAG AND REPLACE
        sf::RectangleShape dragSel;
        bool               dragSelInit; //drag replacement enabled

        void setSelectedObjPos ();
    };

    class EditorState : public State {
        public:
            EditorState(EngineDataRef eData);
            virtual ~EditorState () {}

            void initDragSel ();
            void init ();
            void update (float deltaT);
            void draw (float deltaT);

            void ifKeyPressedEvent (sf::Event &ev);
            void ifKeyReleasedEvent (sf::Event &ev);
            void ifMousePressed (sf::Event& ev);
            void ifMouseReleased (sf::Event& ev);

            void heldControls (Layer& curLay);
            void releasedHeldControls (Layer& curLay);

            void rectBasedSelect ();
            void findExactPosition (int& finPos, unsigned int& finSize,
                                    int rectPos, unsigned int rectSize,
                                    int rectSetPos, unsigned int rectSetSize,
                                    int mousePos);
            void rectBasedReplace (Layer& curLay);
            void determRectReplRange (Layer& curLay, int& startX, int& startY, int& endX, int& endY);
        private :
            EngineDataRef eData;
            EditorDataRef editData = std::make_shared<EditorData>();

            std::map<sf::Keyboard::Key,bool> heldKeys;
            std::map<sf::Mouse::Button,bool> heldMouse;

            sf::Vector2f dragRectSetPos;
            sf::Vector2u dragRectSetSize;
    };
}
