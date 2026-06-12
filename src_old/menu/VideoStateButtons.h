#pragma once

#include "Obj.h"
#include "Game.h"

#include <memory>

namespace RawEngine {

    /////////////////RESOLUTION CHOOSER////////////////////

    typedef VCont::iterator (*Next) (VCont::iterator, int);

    class ResChooser : public Obj{
        public :
            ResChooser(EngineDataRef data, float x, float y, float rot);
            void updateText (float x, float y);
            virtual ~ResChooser() {printf("Destroy %s\n",this->name.c_str());}
            void update (float deltaT);
            void draw (float deltaT);

            void setText (std::string name) {
                this->text.setString(name);
            }

            std::shared_ptr<VCont> _modes;
        private :
            void checkNextType(VCont::iterator& mode, Next next);
            void previousValue();
            void nextValue ();
            bool objectHoveredOver (sf::Vector2i mousePos);

            bool ifKeyPressedEvent (sf::Event &ev);
            bool ifKeyReleasedEvent (sf::Event &ev);
            bool ifMousePressed (sf::Event &ev);
            bool ifMouseReleased (sf::Event &ev);
        protected :
            EngineDataRef eData;
            float xPos,yPos;
            float rot;
            sf::Sprite bg, left, right;
            sf::Text text;
    };

    struct VideoStorage {
        unsigned int bpp;
        VCont cont;
    };

    typedef VideoStorage VS;
    typedef std::vector<VS> VSStorage;
    typedef std::shared_ptr<ResChooser> ResChPtr;

    typedef VSStorage::iterator (*NextBpp) (VSStorage::iterator, int);

    /////////////////BPS(BITS PER PIXEL) CHOOSER////////////////////

    class BPPChooser : public Obj{
        public :
            BPPChooser(EngineDataRef data, float x, float y, float rot, ResChPtr resCh);
            void updateText (float x, float y);
            virtual ~BPPChooser() {printf("Destroy %s\n",this->name.c_str());}
            void update (float deltaT);
            void draw (float deltaT);
        private :
            void checkNextType(VSStorage::iterator& vsSt, NextBpp next);
            void previousValue ();
            void nextValue ();
            bool objectHoveredOver (sf::Vector2i mousePos);

            bool ifKeyPressedEvent (sf::Event &ev);
            bool ifKeyReleasedEvent (sf::Event &ev);
            bool ifMousePressed (sf::Event &ev);
            bool ifMouseReleased (sf::Event &ev);

        protected :
            VSStorage vsStor;
            EngineDataRef eData;
            ResChPtr resCh;
            float xPos,yPos;
            float rot;
            sf::Sprite bg,left, right;
            sf::Text text;
    };

    ////////////SCREEN CONDITION BUTTON (FULLSCREEN OR WINDOWED)
    class ScrnTButton : public Obj
    {
        public:
            ScrnTButton(EngineDataRef data, float x, float y, float scaleX, float scaleY, float rot, std::string name);
            virtual ~ScrnTButton() {printf("Destroy %s\n",this->name.c_str());}

            bool objectHoveredOver (sf::Vector2i mousePos);

            void loadTextures(std::string name);
            void update (float deltaT);
            void draw (float deltaT);

            void performNewWindowAction ();

            bool ifKeyPressedEvent (sf::Event &ev);
            bool ifKeyReleasedEvent (sf::Event &ev);
            bool ifMousePressed (sf::Event &ev);
            bool ifMouseReleased (sf::Event &ev);
        protected :
            sf::Sprite sprite;
            EngineDataRef eData;

            bool butFullScr;
    };

    //////////VIDEO OPTION STATE EXIT BUTTON///////////////

    class VideoExitButton : public Obj
    {
        public:
            VideoExitButton(EngineDataRef data, float x, float y, float scaleX, float scaleY, float rot);
            virtual ~VideoExitButton() {printf("Destroy %s\n",this->name.c_str());}
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
