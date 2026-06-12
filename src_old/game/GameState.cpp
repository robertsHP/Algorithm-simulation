#include "GameState.h"

#include "MenuState.h"
#include "ObjectHandler.h"

namespace RawEngine {
    GameState::GameState(EngineDataRef data) : eData(data)
    {
        objH::loadSpriteSheets(data);
        gData->changePos = sf::Vector2f(0.0f,0.0f);
        gData->lvlName = "testlevel";
        gData->moving = false;
    }
    void GameState::init()
    {
        lh::createGrid(eData, gData->layers, 1, 1);
        lh::loadLevel(eData, gData->layers, gData->lvlName);

        objH::filterUnitsFromLayers(
            gData->playerCont,
            gData->enemyCont,
            gData->layers
        );
//        sf::Vector2i winSize (GD_INPUT.correctPos(GD_WIN,sf::Vector2<int>(GD_WIN.getSize())));
    }

    void GameState::update(float deltaT)
    {
        //CONTROL UPDATES
        if(!gData->moving){
            if(eData->mCursorGrab) {
                lh::cornerMouseControls(
                    GD_WIN.getSize().x,
                    GD_WIN.getSize().y,
                    gData->changePos,
                    GD_WIN
                );
            }
        }
        heldControls ();
        releasedHeldControls();

        std::size_t x, y;

        //OBJ UPDATES
        for(Layer& layer : gData->layers) {
            for(y = 0; y < layer.size(); ++y){
                for(x = 0; x < layer[y].size(); ++x){
                    GameObjPtr obj = layer[y][x];
                    if(gData->changePos.x != 0 || gData->changePos.y != 0){
                        obj->moveSprite(
                            -gData->changePos.x,
                            -gData->changePos.y
                        );
                        obj->prevPos.x -= gData->changePos.x;
                        obj->prevPos.y -= gData->changePos.y;
                    }
                    obj->update(deltaT);
                }
            }
        }
        gData->changePos.x = 0;
        gData->changePos.y = 0;
    }

    void GameState::draw(float deltaT)
    {
        std::size_t i;

        eData->window.clear(sf::Color::Black);

        for(i = 0;i < gData->layers.size(); ++i){
            objH::drawLevelObjects(false, eData, gData->layers[i], deltaT);
        }

        eData->window.display();
    }

    void GameState::ifKeyPressedEvent (sf::Event &ev) {
        std::size_t i;
        ObjPtr      gObj;

        switch(ev.key.code){
            case sf::Keyboard::Escape :
                eData->paused = true;
                GD_MACHINE.addState(StateRef(new MenuState(eData)),false);
                break;
            default : break;
        }
        for(i = 0; i < gData->playerCont.size(); ++i){
            gObj = gData->playerCont[i];
            if(gObj->selected){
                gObj->ifKeyPressedEvent(ev);
            }
        }
        this->heldKeys[ev.key.code] = true;
    }
    void GameState::ifKeyReleasedEvent (sf::Event &ev) {
        this->heldKeys[ev.key.code] = false;
    }
    void GameState::ifMousePressed (sf::Event& ev) {
        std::size_t i;
        ObjPtr gObj;

        for(i = 0; i < gData->playerCont.size(); ++i){
            gObj = gData->playerCont[i];
            if(GD_INPUT.isSpriteClicked(gObj->mainSp, GD_WIN)){
                GD_INPUT.nextWithMouse(i, gData->playerCont);
            }
        }
    }
    void GameState::ifMouseReleased (sf::Event& ev) {

    }

    void GameState::heldControls () {

    }
    void GameState::releasedHeldControls () {

    }
}
