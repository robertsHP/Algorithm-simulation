#pragma once

#include <vector>
#include <memory>

#include "SFML/Graphics.hpp"
#include "TEXTURES.h"
#include "Game.h"
#include "GameObj.h"

namespace RawEngine {

    typedef std::vector<std::vector<GameObjPtr>> Layer;

    enum LevelID {
        TESTLEVEL
    };
    namespace lh {
        bool outsideBounds (sf::Vector2f& pos, Layer& curLay);
        sf::Vector2i findSelectedTileInLayout (EngineDataRef eData, Layer& curLay);
        void cornerMouseControls(int scrnW, int scrnH, sf::Vector2f& changePos,sf::RenderWindow& window);

        void createGrid (EngineDataRef eData, std::vector<Layer>& layers, unsigned int xSize, unsigned int ySize);
        void saveLevel (EngineDataRef eData, std::vector<Layer>& layers, std::string lvlName);
        void loadLevel (EngineDataRef eData, std::vector<Layer>& layers, std::string lvlName);
        bool ifObjectInfo (std::string line, sf::Vector2u& mapSize);
        std::string findLevelFile (LevelID id);
    }
}
