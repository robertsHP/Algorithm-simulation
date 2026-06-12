#pragma once

#include <vector>
#include <memory>

#include "SFML/Graphics.hpp"
#include "TEXTURES.h"
#include "Game.h"
#include "game/GameData.h"

#ifndef G_OBJ_INCL
    #define G_OBJ_INCL
    ////////TILES//////////
    #include "gameobjs/floor_tiles/T_Default.h"
    #include "gameobjs/floor_tiles/T_Grass.h"

    ////////PLAYER//////////////
        #include "gameobjs/units/E_P_Soldier.h"
        #include "gameobjs/units/E_P_Sapper.h"
        #include "gameobjs/units/E_P_Medic.h"
        #include "gameobjs/units/E_P_Tank.h"
    ///////ENEMIES//////////////
        #include "gameobjs/units/E_En_Soldier.h"
#endif

namespace RawEngine {
    typedef std::vector<std::vector<GameObjPtr>> Layer;

    namespace objH {
        void loadSpriteSheets (EngineDataRef eData);
        void replaceObject (EngineDataRef eData, Layer& layer, GameObjID selTileID, int x, int y);
        GameObjPtr newObject (EngineDataRef eData, GameObjID id, GameDataRef gameData);
        void filterUnitsFromLayers (std::vector<ObjPtr>& playerCont,
                                    std::vector<ObjPtr>& enemyCont,
                                    std::vector<Layer>& layers);
        void moveLevelObjects (Layer& layer, sf::Vector2f& lvlPos);
        void drawLevelObjects (bool drawGrid, EngineDataRef eData, Layer& layer, float deltaT);

        bool isGameObjectType (GameObjPtr obj, GameObjID id);
    }
}
