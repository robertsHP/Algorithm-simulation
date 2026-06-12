#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include "Obj.h"

namespace RawEngine {
    class InputManager {
    public:
        InputManager(){}
        virtual ~InputManager(){}

        template<typename T>
        sf::Vector2i correctPos(sf::RenderWindow& window, sf::Vector2<T> pixelPos);

        bool isSpriteClicked(sf::Sprite object, sf::RenderWindow& window);

        bool checkIfMouseWasMoved (sf::RenderWindow& window);
        sf::Vector2i getCorrectMousePos (sf::RenderWindow& window);
        void keepMouseInWindow (sf::RenderWindow& window);

        void nextWithMouse (int index, ObjSt& objSt);

/////////////////////////////////////////////////
        /*
            FOR CHOOSERS LEFT AND RIGHT BUTTONS
        */
        void nextButtonAction (ObjPtr obj, ObjPtr nextObj);
        void nextButton (bool up, ObjSt& objSt);
/////////////////////////////////////////////////
    private :
        sf::Vector2i mousePos;
    };
}
