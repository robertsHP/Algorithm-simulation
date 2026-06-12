#pragma once

#include "Obj.h"
#include "Game.h"
#include "InvItem.h"

namespace RawEngine {

    class GameObj;
    typedef std::shared_ptr<GameObj> GameObjPtr;
    typedef std::vector<GameObjPtr> GameObjSt;

    class GameObj : public Obj {
        public :
            std::string objInfoToString (sf::Vector2i& zeroPos);
            void stringInfoToObj (std::vector<std::string>& info, sf::Vector2u& mapSize, unsigned int layIndex);

            void numpadControls (sf::Event& ev);
            void updateMovement ();
        public :
            GameObjID id;
            unsigned int layIndex;

            bool moving = false;
            bool hidden = false;
            bool solid = false;

            int health;
            int stamina;
            int diceRoll;

            sf::Vector2f prevPos = sf::Vector2f(0,0);
            sf::Vector2f moveNext = sf::Vector2f(0,0);
    };
}
