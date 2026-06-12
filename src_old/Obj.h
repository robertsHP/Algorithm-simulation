#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "SFML/Graphics.hpp"
#include "IDs.h"
#include "TEXTURES.h"

namespace RawEngine {
    class Obj;

    typedef std::shared_ptr<Obj> ObjPtr;
    typedef std::vector<ObjPtr> ObjSt;

    typedef std::unique_ptr<Obj> ObjPtrUNIQUE;
    typedef std::vector<ObjPtrUNIQUE> ObjStUNIQUE;

    class Obj
    {
        public :
            virtual ~Obj () {}
            virtual void update(float deltaT) = 0;
            virtual void draw (float deltaT) = 0;
            virtual bool ifKeyPressedEvent (sf::Event &ev) = 0;
            virtual bool ifKeyReleasedEvent (sf::Event &ev) = 0;
            virtual bool ifMousePressed (sf::Event &ev) = 0;
            virtual bool ifMouseReleased (sf::Event &ev) = 0;

            //Object hover over is virtual because the object could possibly have more than one sprite
            virtual bool objectHoveredOver(sf::Vector2i mousePos) = 0;

        public :
            ///Texture effects
            void checkIfDefaultColorsSet ();
            template <typename Operator> void updateColor (int num, Operator op);
            void glowAnimation (float defaultR, float defaultG, float defaultB);
            void popUpAndDisappearAnim (float deltaT);

            void moveSprite(float x, float y);
        public :
            std::string name;

            sf::Clock clock;
            sf::Sprite mainSp;

            unsigned int r = 255,g = 255,b = 255;
            const float COLOR_UPDATE = 0.0166667;
        public :
            bool selected = false;
            bool bottomObj;
    };

    bool getSpritePosCondition (sf::Vector2i& mousePos, sf::Vector2i& spPos, float xSize, float ySize);
    void setVector(sf::Vector2f& vect, float x, float y);
}
