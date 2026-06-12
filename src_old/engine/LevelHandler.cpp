#include "LevelHandler.h"

#include "OSChecker.h"
#include "VarOperator.h"
#include "ObjectHandler.h"

namespace RawEngine {
    namespace lh {
        bool outsideBounds (sf::Vector2f& pos, Layer& curLay) {
            bool yPos = curLay.size() > pos.y && pos.y > 0;
            bool xPos = curLay[0].size() > pos.x && pos.x > 0;
            return yPos && xPos;
        }
        sf::Vector2i findSelectedTileInLayout (EngineDataRef eData, Layer& curLay) {
            ///Based on mouse position and level grid position on the screen, finds the exact object in a Layout to replace
            sf::Vector2f gridStart, mousePos, objPos;

            mousePos = sf::Vector2f(GD_INPUT.getCorrectMousePos(GD_WIN));
            gridStart = sf::Vector2f(curLay[0][0]->mainSp.getPosition());

            objPos = sf::Vector2f(
                (mousePos.x - gridStart.x) / 25,
                (mousePos.y - gridStart.y) / 25
            );
            if(outsideBounds(objPos,curLay))
                if(GD_INPUT.isSpriteClicked(curLay[objPos.y][objPos.x]->mainSp,GD_WIN))
                    return sf::Vector2i(objPos.x,objPos.y);
            return sf::Vector2i(-1,-1);
        }
        void cornerMouseControls(int scrnW, int scrnH, sf::Vector2f& changePos, sf::RenderWindow& window) {
            sf::Vector2i mousePos(sf::Mouse::getPosition(window));

            int offSet = 2;

            if(mousePos.x < offSet && mousePos.x > -2) changePos.x -= SCRN_MOVE_VEL;
            if(mousePos.y < offSet && mousePos.y > -2) changePos.y -= SCRN_MOVE_VEL;
            if(mousePos.x > scrnW - offSet && mousePos.x < scrnW+2) changePos.x += SCRN_MOVE_VEL;
            if(mousePos.y > scrnH - offSet && mousePos.y < scrnH+2) changePos.y += SCRN_MOVE_VEL;
        }
        void createGrid (EngineDataRef eData, std::vector<Layer>& layers, unsigned int xSize, unsigned int ySize) {
            using namespace std;

            unsigned int l, x, y;
            GameObjPtr   obj;

            for(l = 0; l < LAYER_AMOUNT; ++l){
                Layer layer;
                for(y = 0; y < ySize; ++y){
                    layer.push_back(GameObjSt());
                    for(x = 0; x < xSize; ++x){
                        GameObjPtr obj = objH::newObject(eData, T_DEFAULT, nullptr);
                        obj->mainSp.setPosition(
                            x * TILE_W,
                            y * TILE_H
                        );
                        layer[y].push_back(obj);
                    }
                }
                layers.push_back(layer);
            }
        }
        void saveLevel (EngineDataRef eData, std::vector<Layer>& layers, std::string lvlName) {
            using namespace std;
            using std::to_string;

            size_t x, y;
            string origFile, newFile, line;
            string xSizeStr, ySizeStr;

            origFile = "./levels/"+lvlName+".lvl";
            newFile  = "./levels/"+lvlName+"New.lvl";

            xSizeStr = to_string(layers[0][0].size());
            ySizeStr = to_string(layers[0].size());

            ofstream newLvlFile(newFile);

            try {
                if (newLvlFile.is_open()) {
                    newLvlFile << "x = "+xSizeStr+"\n";
                    newLvlFile << "y = "+ySizeStr+"\n";
                    sf::Vector2i zeroPos (layers[0][0][0]->mainSp.getPosition());
                    for(Layer& layout : layers) {
                        for(y = 0; y < layout.size(); ++y) {
                            for(x = 0; x < layout[y].size(); ++x)
                                line += layout[y][x]->objInfoToString(zeroPos)+"|";
                            newLvlFile << line+"\n";
                            line = "";
                        }
                        newLvlFile << "#\n";
                    }
                    newLvlFile.close();
                } else throw "Couldn't open level file for saving.";
                if (OS_REMOVE(origFile.c_str()) != 0)
                    throw "Failed to remove original level file.";
                if (OS_RENAME(newFile.c_str(),origFile.c_str()) != 0)
                    throw "Failed to rename level file.";
            } catch (char* exc) {
                printf("%s\n", exc);
            }
        }
        void loadLevel (EngineDataRef eData, std::vector<Layer>& layers, std::string lvlName) {
            using namespace std;

            vector<string> splitRow, objInfo;
            string         line;
            unsigned int   layIndex;
            sf::Vector2u   mapSize;
            size_t         x;

            ifstream lvlFile("./levels/"+lvlName+".lvl");

            if(lvlFile.is_open()) {
                layIndex = 0;
                for(Layer& layer : layers) {
                    layer.clear();
                    while (getline (lvlFile,line)) {
                        GameObjSt objCont;
                        if(line.find('#') != string::npos) {
                            break;
                        } else if (!ifObjectInfo(line, mapSize)) {
                            continue;
                        }
                        splitRow = VarOp::split(line,"|");
                        for(x = 0; x < splitRow.size(); ++x){
                            objInfo = VarOp::split(splitRow[x],";");
                            objCont.push_back(objH::newObject(
                                eData,
                                (GameObjID) stoi(objInfo[0]),
                                nullptr
                            ));
                            objCont[x]->stringInfoToObj(objInfo, mapSize, layIndex);
                        }
                        layer.push_back(objCont);
                    }
                    layIndex++;
                }
                lvlFile.close();
            } else printf("Couldn't open level file for loading.\n");
        }
        bool ifObjectInfo (std::string line, sf::Vector2u& mapSize) {
            switch(line.c_str()[0]) {
                case 'x' : mapSize.x = VarOp::uintFstr(4, line.size(), line); return false;
                case 'y' : mapSize.y = VarOp::uintFstr(4, line.size(), line); return false;
                default : return true;
            }
        }
        std::string findLevelFile (LevelID id) {
            switch(id){
                default : return "testlevel";
            }
        }
    }
}
