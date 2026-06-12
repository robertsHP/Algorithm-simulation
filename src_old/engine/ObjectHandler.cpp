#include "ObjectHandler.h"

namespace RawEngine {
    namespace objH {
        void loadSpriteSheets (EngineDataRef eData) {
            GD_ASSETS.loadTexture("T_GROUND", T_GROUND);
            GD_ASSETS.loadTexture("E_UNITS", E_UNITS);
        }
        void replaceObject (EngineDataRef eData, Layer& layer, GameObjID selTileID, int x, int y) {
            if(selTileID != layer[y][x]->id) {
                sf::Vector2f pos (layer[y][x]->mainSp.getPosition());
                sf::Color color  (layer[y][x]->mainSp.getColor());

                GameObjPtr selTile (objH::newObject(eData, selTileID, nullptr));
                selTile->mainSp.setPosition(pos.x,pos.y);
                selTile->mainSp.setRotation(layer[y][x]->mainSp.getRotation());
                layer[y][x] = selTile;
            }
        }
        GameObjPtr newObject (EngineDataRef eData, GameObjID id, GameDataRef gameData) {
            switch(id){
                ///TILES
                    case GameObjID::T_GRASSNORMAL : return GameObjPtr(new T_Grass(eData, gameData));
                ///ENTITIES
                    //PLAYER
                    case GameObjID::E_P_SOLDIER : return GameObjPtr(new E_P_Soldier(eData, gameData));
//                    case GameObjID::E_P_SAPPER : return GameObjPtr(new E_P_Sapper(eData));
//                    case GameObjID::E_P_MEDIC : return GameObjPtr(new E_P_Medic(eData));
//                    case GameObjID::E_P_TANK : return GameObjPtr(new E_P_Tank(eData));
                    //ENEMIES
//                    case GameObjID::E_EN_SOLDIER : return GameObjPtr(new E_En_Soldier(eData));
                default : return GameObjPtr(new T_Default(eData, gameData));
            }
        }
        void filterUnitsFromLayers (std::vector<ObjPtr>& playerCont,
                                    std::vector<ObjPtr>& enemyCont,
                                    std::vector<Layer>& layers) {
            unsigned int x, y;

            for(Layer& layer : layers){
                for(y = 0; y < layer.size() ;++y){
                    for(x = 0; x < layer[y].size() ;++x){
                        switch (layer[y][x]->id){
                            case E_P_SOLDIER :
                            case E_P_SAPPER :
                            case E_P_MEDIC :
                            case E_P_TANK :
                                playerCont.push_back(layer[y][x]);
                                break;
                            case E_EN_SOLDIER :
                            case E_EN_SAPPER :
                            case E_EN_MEDIC :
                            case E_EN_TANK :
                                enemyCont.push_back(layer[y][x]);
                                break;
                            default : break;
                        }
                    }
                }
            }
        }
        void moveLevelObjects (Layer& layer, sf::Vector2f& lvlPos) {
            std::size_t y, x;
            for(y = 0; y < layer.size(); ++y){
                for(x = 0; x < layer[y].size(); ++x){
                    layer[y][x]->moveSprite(-lvlPos.x,-lvlPos.y);
                }
            }
        }
        void drawLevelObjects (bool drawGrid, EngineDataRef eData, Layer& layer, float deltaT) {
            std::size_t x, y;
            for(y = 0;y < layer.size(); ++y){
                for(x = 0;x < layer[y].size(); ++x){
                    if(!drawGrid){
                        if(!objH::isGameObjectType(layer[y][x],T_DEFAULT))
                            layer[y][x]->draw(deltaT);
                    } else {
                        layer[y][x]->draw(deltaT);
                    }
                }
            }
        }

        bool isGameObjectType (GameObjPtr obj, GameObjID id){
            return obj->id == id;
        }
    }
}
