#include "InputManager.h"

namespace RawEngine {
    template<typename T>
    sf::Vector2i InputManager::correctPos(sf::RenderWindow& window,sf::Vector2<T> pixelPos)
    {
        sf::Vector2f worldPos (window.mapPixelToCoords(sf::Vector2i(pixelPos)));
        sf::Vector2i finalPos (worldPos.x,worldPos.y);
        return finalPos;
    }

    bool InputManager::isSpriteClicked(sf::Sprite object, sf::RenderWindow& window)
    {
        sf::IntRect tempRect (
            object.getPosition().x,
            object.getPosition().y,
            object.getGlobalBounds().width,
            object.getGlobalBounds().height
        );
        return tempRect.contains(getCorrectMousePos(window));
    }

    bool InputManager::checkIfMouseWasMoved (sf::RenderWindow& window) {
        return getCorrectMousePos(window) != mousePos;
    }
    sf::Vector2i InputManager::getCorrectMousePos(sf::RenderWindow& window) {
        return correctPos(window,sf::Mouse::getPosition(window));
    }
    void InputManager::nextWithMouse (int index, ObjSt& objSt) {
        for(std::size_t i = 0;i<objSt.size();++i){
            if(objSt[i]->selected){
                objSt[i]->selected = false;
            }
        }
        objSt[index]->selected = true;
    }

/////////////////////////////////////////////////
    /*
        FOR CHOOSERS LEFT AND RIGHT BUTTONS
    */
    void InputManager::nextButtonAction (ObjPtr obj, ObjPtr nextObj) {
        obj->selected = false;
        nextObj->selected = true;
    }
    void InputManager::nextButton (bool up, ObjSt& objSt) {
        for(std::size_t i = 0;i<objSt.size();++i){
            ObjPtr obj (objSt[i]);

            if(up && obj != objSt.front()){
                if(obj->selected){
                    nextButtonAction(obj,objSt[i-1]);
                }
            } else if (!up && obj != objSt.back()) {
                if(obj->selected){
                    nextButtonAction(obj,objSt[i+1]);
                    break;
                }
            }
        }
    }
/////////////////////////////////////////////////////
}
