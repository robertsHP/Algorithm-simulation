#include "GameObj.h"

namespace RawEngine {
    std::string GameObj::objInfoToString (sf::Vector2i& zeroPos) {
        using std::to_string;

        sf::Vector2i pos (this->mainSp.getPosition());
        return to_string(this->id)+";"+
               to_string((pos.x - zeroPos.x) / TILE_W)+";"+
               to_string((pos.y - zeroPos.y) / TILE_H)+";"+
               to_string(this->mainSp.getRotation())+";";
    }
    void GameObj::stringInfoToObj (std::vector<std::string>& info, sf::Vector2u& mapSize, unsigned int layIndex) {
        using std::stof;

        this->layIndex = layIndex;
        this->mainSp.setPosition(
            stof(info[1]) * TILE_W,
            stof(info[2]) * TILE_H
        );
        this->mainSp.setRotation(stof(info[3]));
    }
    void GameObj::numpadControls (sf::Event& ev) {
        if(!this->moving) {
            switch(ev.key.code){
                case sf::Keyboard::Q : setVector(this->moveNext,-1, -1);  break;
                case sf::Keyboard::W : setVector(this->moveNext, 0, -1);  break;
                case sf::Keyboard::E : setVector(this->moveNext, 1, -1);  break;
                case sf::Keyboard::A : setVector(this->moveNext,-1,  0);  break;
                case sf::Keyboard::D : setVector(this->moveNext, 1,  0);  break;
                case sf::Keyboard::Z : setVector(this->moveNext,-1,  1);  break;
                case sf::Keyboard::X : setVector(this->moveNext, 0,  1);  break;
                case sf::Keyboard::C : setVector(this->moveNext, 1,  1);  break;
                default : break;
            }
            if(this->moveNext.x != 0 || this->moveNext.y != 0){
                this->moving = true;
                this->prevPos = this->mainSp.getPosition();
            }
        }
    }
    void GameObj::updateMovement () {
        this->mainSp.move(moveNext.x,moveNext.y);

        sf::Vector2f mainPos (this->mainSp.getPosition());

        float nextX = this->prevPos.x + (TILE_W * moveNext.x);
        float nextY = this->prevPos.y + (TILE_H * moveNext.y);

        if(moveNext.x == 0 || nextX == mainPos.x){
            if(moveNext.y == 0 || nextY == mainPos.y){
                setVector(this->moveNext,0,0);
                this->moving = false;
            }
        }
    }
}
