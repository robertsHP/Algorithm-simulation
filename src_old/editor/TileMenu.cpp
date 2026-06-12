#include "TileMenu.h"

namespace RawEngine {
    TileMenu::TileMenu(EditorDataRef editData, EngineDataRef eData) : eData(eData), editData(editData)
    {
        GD_ASSETS.loadAndSet("ED_LEFT",ED_LEFT,this->left);
        GD_ASSETS.loadAndSet("TM_MENU",TM_MENU,this->menu);
        GD_ASSETS.loadAndSet("ED_RIGHT",ED_RIGHT,this->right);
        init();
    }
    void TileMenu::init () {

        sf::Vector2u winSize (GD_INPUT.correctPos(GD_WIN,sf::Vector2<int>(GD_WIN.getSize())));
        this->leftSize = this->left.getTexture()->getSize();
        this->menuSize = this->menu.getTexture()->getSize();
        this->rightSize = this->right.getTexture()->getSize();
        this->selSize = editData->sel.getTexture()->getSize();

        this->right.setPosition(winSize.x-selSize.x-rightSize.x,winSize.y-leftSize.y);
        this->menu.setPosition(winSize.x-selSize.x-rightSize.x-menuSize.x, winSize.y-menuSize.y);
        this->left.setPosition(winSize.x-selSize.x-rightSize.x-menuSize.x-leftSize.x, winSize.y-leftSize.y);

        editData->sel.setPosition(leftSize.x+menuSize.x+rightSize.x, winSize.y-selSize.y);

        loadTileMenuTiles();
    }
    void TileMenu::loadTileMenuTiles () {
        sf::Vector2i menuPos (this->menu.getPosition());

        std::size_t i = 0;
        sf::Vector2f prevPos;
        while (true) {
            GameObjSt tileGrid;
            for(std::size_t j = 0;j<14;++j,++i){
                if(i == GameObjID::T_LAST) break;
                GameObjPtr newGObj (objH::newObject(eData,(GameObjID)i, nullptr));

                switch(j){
                    case 0 : newGObj->mainSp.setPosition(menuPos.x+2,menuPos.y+25); break;
                    case 7 : newGObj->mainSp.setPosition(menuPos.x+2,menuPos.y+26+28); break;
                    default : newGObj->mainSp.setPosition(prevPos.x+29,prevPos.y); break;
                }
                prevPos = newGObj->mainSp.getPosition();

                newGObj->mainSp.setRotation(0);
                tileGrid.push_back(newGObj);
            }
            this->tmObjs.push_back(tileGrid);
            if(i == GameObjID::T_LAST) break;
        }
    }
    void TileMenu::update (float deltaT) {
        for(std::size_t tIndex = 0;tIndex < this->tmObjs[this->tmObjSel].size();++tIndex){
            tmObjs[tmObjSel][tIndex]->update(deltaT);
        }
    }
    void TileMenu::draw(float deltaT){
        GD_WIN.draw(this->left);
        GD_WIN.draw(this->menu);
        GD_WIN.draw(this->right);

        for(std::size_t tIndex = 0; tIndex < this->tmObjs[this->tmObjSel].size();++tIndex){
            tmObjs[tmObjSel][tIndex]->draw(deltaT);
        }
    }
    bool TileMenu::ifKeyPressedEvent(sf::Event& ev) {
        return false;
    }

    bool TileMenu::ifKeyReleasedEvent(sf::Event& ev) {
        return false;
    }

    bool TileMenu::ifMousePressed(sf::Event& ev) {
        if(ev.mouseButton.button == sf::Mouse::Left){
            if(GD_INPUT.isSpriteClicked(this->menu, GD_WIN)){
                std::size_t tIndex;

                for(tIndex = 0; tIndex < this->tmObjs[this->tmObjSel].size(); ++tIndex){

                    GameObjPtr& gObj = this->tmObjs[tmObjSel][tIndex];

                    if(GD_INPUT.isSpriteClicked(gObj->mainSp, GD_WIN)){
                        editData->selID = gObj->id;
                        editData->selObj = objH::newObject(eData,gObj->id, nullptr);
                        editData->setSelectedObjPos();
                        break;
                    }
                }
                return true;
            }
            if(GD_INPUT.isSpriteClicked(this->left, GD_WIN)){
                if(this->tmObjSel != 0){
                    --this->tmObjSel;
                }
                return true;
            } else if(GD_INPUT.isSpriteClicked(this->right, GD_WIN)){
                if(this->tmObjSel != this->tmObjs.size()-1){
                    ++this->tmObjSel;
                }
                return true;
            }
        }
        return false;
    }

    bool TileMenu::ifMouseReleased(sf::Event& ev) {
        return false;
    }
}
