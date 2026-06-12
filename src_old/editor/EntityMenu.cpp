#include "EntityMenu.h"

namespace RawEngine {
    EntityMenu::EntityMenu(EditorDataRef editData, EngineDataRef eData) : eData(eData), editData(editData)
    {
        GD_ASSETS.loadAndSet("ED_UP",ED_UP,this->up);
        GD_ASSETS.loadAndSet("EM_MENU",EM_MENU,this->menu);
        GD_ASSETS.loadAndSet("ED_DOWN",ED_DOWN,this->down);

        init();
    }
    void EntityMenu::init () {

        sf::Vector2u winSize (GD_INPUT.correctPos(GD_WIN,sf::Vector2<int>(GD_WIN.getSize())));
        this->upSize = this->up.getTexture()->getSize();
        this->menuSize = this->menu.getTexture()->getSize();
        this->downSize = this->down.getTexture()->getSize();
        this->selSize = editData->sel.getTexture()->getSize();

        this->menu.setPosition(
            winSize.x - menuSize.x,
            winSize.y - menuSize.y - selSize.y
        );
        this->up.setPosition(
            menu.getPosition().x + 25,
            menu.getPosition().y + 17
        );
        this->down.setPosition(
            menu.getPosition().x + 25,
            (menuSize.y + menu.getPosition().y) - (downSize.y + 3)
        );
        editData->sel.setPosition(
            winSize.x - selSize.x,
            menu.getPosition().y + menuSize.y
        );

        loadTileMenuTiles();
    }
    void EntityMenu::loadTileMenuTiles () {
        sf::Vector2i menuPos;
        std::size_t  i;
        sf::Vector2f prevPos;

        i = GameObjID::E_P_SOLDIER;
        menuPos = sf::Vector2i(this->menu.getPosition());

        while (true) {
            GameObjSt tileGrid;
            for(std::size_t j = 0; j < 24; ++j, ++i){
                if(i == GameObjID::E_LAST) break;
                GameObjPtr newGObj (objH::newObject(eData, (GameObjID)i, nullptr));
                if(j == 0 || j % 4 == 0) {
                    newGObj->mainSp.setPosition(
                        menuPos.x + 3,
                        menuPos.y + 44.5f + j / 4 * 28.7f
                    );
                } else {
                    newGObj->mainSp.setPosition(
                        prevPos.x + 29,
                        prevPos.y
                    );
                }
                prevPos = newGObj->mainSp.getPosition();

                newGObj->mainSp.setRotation(0);
                tileGrid.push_back(newGObj);
            }
            this->entMObjs.push_back(tileGrid);
            if(i == GameObjID::E_LAST) break;
        }
    }
    void EntityMenu::update (float deltaT) {
        for(std::size_t tIndex = 0; tIndex < this->entMObjs[this->selObj].size(); ++tIndex){
            entMObjs[selObj][tIndex]->update(deltaT);
        }
    }
    void EntityMenu::draw(float deltaT){
        GD_WIN.draw(this->menu);
        GD_WIN.draw(this->up);
        GD_WIN.draw(this->down);

        for(std::size_t tIndex = 0; tIndex < this->entMObjs[this->selObj].size(); ++tIndex){
            entMObjs[selObj][tIndex]->draw(deltaT);
        }
    }
    bool EntityMenu::ifKeyPressedEvent(sf::Event& ev) {
        return false;
    }

    bool EntityMenu::ifKeyReleasedEvent(sf::Event& ev) {
        return false;
    }

    bool EntityMenu::ifMousePressed(sf::Event& ev) {
        if(ev.mouseButton.button == sf::Mouse::Left){
            if(GD_INPUT.isSpriteClicked(this->menu, GD_WIN)){
                std::size_t tIndex;
                unsigned int entMObjSize = this->entMObjs[this->selObj].size();

                for(tIndex = 0; tIndex < entMObjSize ;++tIndex){
                    if(GD_INPUT.isSpriteClicked(this->entMObjs[selObj][tIndex]->mainSp,GD_WIN)){
                        editData->selID = entMObjs[selObj][tIndex]->id;
                        editData->selObj = objH::newObject(eData, entMObjs[selObj][tIndex]->id, nullptr);
                        editData->setSelectedObjPos();
                        break;
                    }
                }
                if(GD_INPUT.isSpriteClicked(this->up, GD_WIN)){
                    if(this->selObj != 0){
                        this->selObj--;
                    }
                } else if(GD_INPUT.isSpriteClicked(this->down, GD_WIN)){
                    if(this->selObj != this->entMObjs.size() - 1){
                        this->selObj++;
                    }
                }
                return true;
            }
        }
        return false;
    }

    bool EntityMenu::ifMouseReleased(sf::Event& ev) {
        return false;
    }
}
