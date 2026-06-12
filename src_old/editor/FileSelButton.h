#pragma once

#include "EditorState.h"

namespace RawEngine {
    class FileSelButton : public Obj
    {
        public:
            FileSelButton(EditorDataRef editData, EngineDataRef eData, float x, float y, float scaleX, float scaleY, float rot);
            virtual ~FileSelButton() {printf("Destroy %s\n",this->name.c_str());}
            void loadTextures();
            void init();
            bool objectHoveredOver (sf::Vector2i mousePos);
            void update (float deltaT);
            void draw (float deltaT);

            bool ifKeyPressedEvent (sf::Event &ev);
            bool ifKeyReleasedEvent (sf::Event &ev);

            bool ifMousePressed (sf::Event &ev);
            bool ifMouseReleased (sf::Event &ev);
        public :
            sf::Sprite sprite;
            EditorDataRef editData;
            EngineDataRef eData;
            ObjSt objSt;
    };

////////////////CHILD BUTTONS/////////////

    //////////SAVE////////////////

    class FileSaveBut : public Obj
    {
        public:
            FileSaveBut(EditorDataRef editData, EngineDataRef eData, float x, float y, float scaleX, float scaleY, float rot);
            virtual ~FileSaveBut() {printf("Destroy %s\n",this->name.c_str());}
            void loadTextures();
            bool objectHoveredOver (sf::Vector2i mousePos);
            void update (float deltaT);
            void draw (float deltaT);

            bool ifKeyPressedEvent (sf::Event &ev);
            bool ifKeyReleasedEvent (sf::Event &ev);

            bool ifMousePressed (sf::Event &ev);
            bool ifMouseReleased (sf::Event &ev);
        public :
            sf::Sprite sprite;
            EditorDataRef editData;
            EngineDataRef eData;
    };

    /////////LOAD///////////

    class FileLoadBut : public Obj
    {
        public:
            FileLoadBut(EditorDataRef editData, EngineDataRef eData, float x, float y, float scaleX, float scaleY, float rot);
            virtual ~FileLoadBut() {printf("Destroy %s\n",this->name.c_str());}
            void loadTextures();
            bool objectHoveredOver (sf::Vector2i mousePos);
            void update (float deltaT);
            void draw (float deltaT);

            bool ifKeyPressedEvent (sf::Event &ev);
            bool ifKeyReleasedEvent (sf::Event &ev);

            bool ifMousePressed (sf::Event &ev);
            bool ifMouseReleased (sf::Event &ev);
        public :
            sf::Sprite sprite;
            EditorDataRef editData;
            EngineDataRef eData;
    };

    /////////////////EXIT/////////////

    class FileExitBut : public Obj
    {
        public:
            FileExitBut(EditorDataRef editData, EngineDataRef eData, float x, float y, float scaleX, float scaleY, float rot);
            virtual ~FileExitBut() {printf("Destroy %s\n",this->name.c_str());}
            void loadTextures();
            bool objectHoveredOver (sf::Vector2i mousePos);
            void update (float deltaT);
            void draw (float deltaT);

            bool ifKeyPressedEvent (sf::Event &ev);
            bool ifKeyReleasedEvent (sf::Event &ev);

            bool ifMousePressed (sf::Event &ev);
            bool ifMouseReleased (sf::Event &ev);
        public :
            sf::Sprite sprite;
            EditorDataRef editData;
            EngineDataRef eData;
    };
}
