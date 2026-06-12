#pragma once

#include <vector>
#include <memory>
#include <string>

#include "GameObj.h"

namespace RawEngine {

    struct GameData;
    typedef std::shared_ptr<GameData> GameDataRef;
    typedef std::vector<std::vector<GameObjPtr>> Layer;

    struct GameData {
        std::vector<Layer> layers;
        sf::Vector2f       changePos;

        std::vector<ObjPtr> playerCont;
        std::vector<ObjPtr> enemyCont;
        bool                moving;

        std::string lvlName;

        ObjStUNIQUE mObjCont;
    };
}
