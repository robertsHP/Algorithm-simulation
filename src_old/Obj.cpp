#include "Obj.h"
#include "Game.h"

namespace RawEngine {
    void Obj::moveSprite(float x, float y) {
        this->mainSp.move(x,y);
    }

///////////////////SPRITE ANIMATIONS WHEN SELECTED//////////////////////////////////////////

    void Obj::checkIfDefaultColorsSet () {
        if(this->mainSp.getColor() != sf::Color(this->r,this->g,this->b,255)){
            this->mainSp.setColor(sf::Color(this->r,this->g,this->b,255));
            this->clock.restart();
        }
    }
    template <typename Operator>
    void Obj::updateColor (int num, Operator op) {
        this->r = op(this->r, COLOR_UPDATE*num);
        this->g = op(this->g, COLOR_UPDATE*num);
        this->b = op(this->b, COLOR_UPDATE*num);
    }
    void Obj::glowAnimation (float defaultR, float defaultG, float defaultB) {
        bool rgbLimit = this->r > defaultR || this->g > defaultG || this->b > defaultB;
        if(rgbLimit || this->clock.getElapsedTime().asSeconds() > 2){
            this->clock.restart();
            this->r = defaultR;
            this->g = defaultG;
            this->b = defaultB;
        } else if(this->clock.getElapsedTime().asSeconds()>1){
            updateColor(135,std::plus<int>());
        } else {
            updateColor(135,std::minus<int>());
        }
    }
    void Obj::popUpAndDisappearAnim (float deltaT) {
        float time = this->clock.getElapsedTime().asSeconds();

        if(time < 0.1){
            this->mainSp.setColor(sf::Color(this->r,this->g,this->b,255));
        } else if(time > 0.1){
            this->mainSp.setColor(sf::Color(this->r,this->g,this->b,0));
        }
        if(time > 0.5){
            this->clock.restart();
        }
    }

//////////////////////////////////////////////////////////////////////////////////////

    bool getSpritePosCondition (sf::Vector2i& mousePos, sf::Vector2i& spPos, float xSize, float ySize) {
        bool detectX = mousePos.x >= spPos.x && mousePos.x < spPos.x + xSize;
        bool detectY = mousePos.y >= spPos.y && mousePos.y < spPos.y + ySize;
        return detectX && detectY;
    }
    void setVector(sf::Vector2f& vect, float x, float y) {
        vect.x = x;
        vect.y = y;
    }
}
