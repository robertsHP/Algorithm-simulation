#include <sstream>
#include <iostream>
#include <algorithm>

#include "EditorState.h"
#include "MenuState.h"
#include "FileSelButton.h"
#include "TileMenu.h"
#include "EntityMenu.h"
#include "LayerMenu.h"

namespace RawEngine {
/*
///////////////////////////////////////////////////////////////////////////////////////
///////////////////// EDITOR DATA //////////////////////
///////////////////////////////////////////////////////////////////////////////////////
*/
    void EditorData::setSelectedObjPos () {
        sf::Vector2i selPos (sel.getPosition());
        selObj->mainSp.setPosition(selPos.x+20,selPos.y+33);
    }
/*
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////EDITOR STATE///////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
*/
    EditorState::EditorState(EngineDataRef eData) : eData(eData){
        objH::loadSpriteSheets(eData);
        editData->lvlName = "testlevel";
        editData->changePos = sf::Vector2f(0.0f,0.0f);
        editData->drawGrid = true;

        initDragSel();
    }
    void EditorState::initDragSel () {
        editData->dragSel.setOutlineColor(sf::Color::Cyan);
        editData->dragSel.setOutlineThickness(1);
        editData->dragSel.setPosition(0,0);
        editData->dragSel.setSize(sf::Vector2f(25,25));
        editData->dragSel.setFillColor(sf::Color::Transparent);
        editData->dragSelInit = false;
    }
    void EditorState::init()
    {
        lh::createGrid(eData, editData->layers, 10, 10);

//        sf::Vector2i winSize (GD_INPUT.correctPos(GD_WIN,sf::Vector2<int>(GD_WIN.getSize())));
        GD_ASSETS.loadAndSet("ED_SEL",ED_SEL,editData->sel);

        editData->mObjCont.clear();
        editData->mObjCont.push_back(std::unique_ptr<Obj>(new LayerMenu(
            editData,
            eData)));
        editData->mObjCont.push_back(std::unique_ptr<Obj>(new TileMenu(
            editData,
            eData)));
        editData->mObjCont.push_back(std::unique_ptr<Obj>(new EntityMenu(
            editData,
            eData)));
        editData->mObjCont.push_back(std::unique_ptr<Obj>(new FileSelButton(
            editData,
            eData,
            0,0,1,1,GD_CONFIG_ST->rot)));

        editData->selObj = objH::newObject(eData, editData->selID, nullptr);
        editData->setSelectedObjPos();
    }

    void EditorState::update(float deltaT)
    {
        //CONTROL UPDATES
        if(eData->mCursorGrab) {
            lh::cornerMouseControls(
                GD_WIN.getSize().x,
                GD_WIN.getSize().y,
                editData->changePos,
                GD_WIN
            );
        }
        Layer& curLay = editData->layers[editData->selLayer];

        heldControls (curLay);
        releasedHeldControls(curLay);

        //LEVEL UPDATES
        std::size_t x, y;

        if(editData->changePos.x != 0 || editData->changePos.y != 0){
            for(Layer& layer : editData->layers) {
                for(y = 0; y < layer.size(); ++y){
                    for(x = 0; x < layer[y].size(); ++x){
                        layer[y][x]->moveSprite(
                            -editData->changePos.x,
                            -editData->changePos.y
                        );
                    }
                }
            }
            if(editData->dragSelInit){
                dragRectSetPos.x += -editData->changePos.x;
                dragRectSetPos.y += -editData->changePos.y;
            }
            editData->dragSel.move(
                -editData->changePos.x,
                -editData->changePos.y
            );
            editData->changePos.x = 0;
            editData->changePos.y = 0;
        }

        for(auto& mObj : editData->mObjCont){
            mObj->update(deltaT);
        }
    }

    void EditorState::draw(float deltaT)
    {
        eData->window.clear(sf::Color::Black);

        for(auto& mObj : editData->mObjCont)
            mObj->draw(deltaT);

        GD_WIN.draw(editData->sel);
        editData->selObj->draw(deltaT);

        eData->window.display();
    }
    /*
//////////////////////////////////////////////////////////////////
            STATE INPUT
//////////////////////////////////////////////////////////////////
    */
    void EditorState::ifKeyPressedEvent (sf::Event &ev) {
        this->heldKeys[ev.key.code] = true;

        for(auto& mObj : editData->mObjCont)
            if(mObj->ifKeyPressedEvent(ev))
                return;

        switch(ev.key.code) {
            case sf::Keyboard::Escape :
                eData->paused = true;
                GD_MACHINE.addState(StateRef(new MenuState(eData)),false);
                break;
            case sf::Keyboard::D :
                if(editData->drawGrid){
                    editData->drawGrid = false;
                } else {
                    editData->drawGrid = true;
                }
                break;
            default : break;
        }
    }
    void EditorState::ifKeyReleasedEvent (sf::Event &ev) {
        ////Held controls///////////////////////////////////
        this->heldKeys[ev.key.code] = false;

        for(auto& mObj : editData->mObjCont)
            if(mObj->ifKeyReleasedEvent(ev))
                return;
    }
    void EditorState::ifMousePressed(sf::Event& ev){
        for(int i = editData->mObjCont.size() - 1 ;i > -1; --i)
            if(editData->mObjCont[i]->ifMousePressed(ev))
                return;

        if(GD_INPUT.isSpriteClicked(editData->sel, GD_WIN))
            return;
        ////Drag selection initiation////////////////////////////////////
        if(ev.mouseButton.button == sf::Mouse::Right)
        {
            editData->dragSel.setPosition(sf::Vector2f(GD_INPUT.getCorrectMousePos(GD_WIN)));
            editData->dragSel.setSize(sf::Vector2f(0,0));
            dragRectSetPos = sf::Vector2f(editData->dragSel.getPosition());
            dragRectSetSize = sf::Vector2u(editData->dragSel.getSize());
            editData->dragSelInit = true;
        }
        ////Held controls///////////////////////////////////
        this->heldMouse[ev.mouseButton.button] = true;
    }

    void EditorState::ifMouseReleased(sf::Event& ev){
        ////Loops over all menu objects to prevent objects drawn behind the object being clicked on
        for(auto& mObj : editData->mObjCont){
            if(mObj->ifMouseReleased(ev))
                return;
        }
        ////Held controls///////////////////////////////////
        this->heldMouse[ev.mouseButton.button] = false;
    }

    /*
    /////////////////////////////////////////////////////////
                        STATE HELD CONTROLS
    /////////////////////////////////////////////////////////
    */
    void EditorState::heldControls (Layer& curLay) {
        if(heldKeys[sf::Keyboard::Up]) editData->changePos.y -= SCRN_MOVE_VEL;
        if(heldKeys[sf::Keyboard::Down]) editData->changePos.y += SCRN_MOVE_VEL;
        if(heldKeys[sf::Keyboard::Left]) editData->changePos.x -= SCRN_MOVE_VEL;
        if(heldKeys[sf::Keyboard::Right]) editData->changePos.x += SCRN_MOVE_VEL;

/////////Drag selection
        if(GD_INPUT.checkIfMouseWasMoved(GD_WIN)){
            if(heldMouse[sf::Mouse::Left]){
                sf::Vector2i selObjLoc (lh::findSelectedTileInLayout(eData,curLay));

                if(selObjLoc.x != -1 && selObjLoc.y != -1){
                    ///generic draw editing
                    objH::replaceObject(eData,curLay,editData->selID, selObjLoc.x, selObjLoc.y);
                }
            } else if (heldMouse[sf::Mouse::Right]) {
                ///rectangle based tile editing
                rectBasedSelect();
            }
        }
    }
    void EditorState::releasedHeldControls (Layer& curLay) {
        ///MULTIPLE TILE REPLACEMENT
        if(!heldMouse[sf::Mouse::Right] && editData->dragSelInit){
            rectBasedReplace(curLay);
        }
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////
/////////RECTANGLE BASED SELECTION/////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
    void EditorState::rectBasedSelect () {
        int posX, posY;
        unsigned int sizeX, sizeY;

        sf::Vector2f mousePos (sf::Vector2f(GD_INPUT.getCorrectMousePos(GD_WIN)));

        sf::Vector2f dragRectPos (editData->dragSel.getPosition());
        sf::Vector2u dragRectSize (editData->dragSel.getSize());

        posX = dragRectPos.x;
        sizeX = dragRectSize.x;
        posY = dragRectPos.y;
        sizeY = dragRectSize.y;

        findExactPosition(
            posX,sizeX,
            dragRectPos.x,dragRectSize.x,
            dragRectSetPos.x,dragRectSetSize.x,
            mousePos.x
        );
        findExactPosition(
            posY,sizeY,
            dragRectPos.y,dragRectSize.y,
            dragRectSetPos.y,dragRectSetSize.y,
            mousePos.y
        );

        editData->dragSel.setPosition(posX,posY);
        editData->dragSel.setSize(sf::Vector2f(sizeX,sizeY));
    }
    void EditorState::findExactPosition(int& finPos, unsigned int& finSize,
                                        int rectPos,unsigned int rectSize,
                                        int rectSetPos, unsigned int rectSetSize,
                                        int mousePos){
        finPos = rectPos;
        finSize = rectSize;

        if (mousePos < rectSetPos){
            finPos = mousePos;
            finSize = rectSetPos - mousePos;
        } else if (mousePos > rectSetPos) {
            finPos = rectSetPos;
            finSize = mousePos - rectSetPos;
        }
    }
    void EditorState::rectBasedReplace (Layer& curLay) {
        int x, y; ///loop index
        int startX, startY, endX, endY;

        determRectReplRange(curLay, startX, startY, endX, endY);

        for(y = startY; y < endY; ++y){
            for(x = startX; x < endX; ++x){
                //prevents a segfault because there are no game objects stored beyond -1 in x and y
                if(x >= 0 && y >= 0) {
                    objH::replaceObject(eData,curLay,editData->selID, x, y);
                }
            }
        }
        editData->dragSelInit = false;
    }
    void EditorState::determRectReplRange (Layer& curLay,
                                            int& startX, int& startY,
                                            int& endX, int& endY)
    {
        sf::Vector2i firstPos (curLay[0][0]->mainSp.getPosition());

        sf::Vector2f dragRectStart (editData->dragSel.getPosition());
        dragRectStart.x -= firstPos.x;
        dragRectStart.y -= firstPos.y;

        sf::Vector2f dragRectEnd (editData->dragSel.getSize());
        dragRectEnd.x += dragRectStart.x;
        dragRectEnd.y += dragRectStart.y;

        //modulus values
        int startModX = (int)dragRectStart.x % TILE_W;
        int startModY = (int)dragRectStart.y % TILE_H;
        int endModX   = (int)dragRectEnd.x % TILE_W;
        int endModY   = (int)dragRectEnd.y % TILE_H;

        /*
            (pos - modulus) / tile size
            Removes modulus value from the position so that it can be divided by the tile size
            to get the tile location in a layer container.
        */
        startX = (dragRectStart.x - startModX) / TILE_W;
        startY = (dragRectStart.y - startModY) / TILE_H;

        /*
            (pos - (tile size - modulus)) / tile size
            Adds to modulus value in the position so that it can be divided by the tile size
            to get the tile location in a layer container.
        */
        endX = (dragRectEnd.x + (TILE_W - endModX)) / TILE_W;
        endY = (dragRectEnd.y + (TILE_H - endModY)) / TILE_H;

        //In case the end is out of bounds to prevent a segmentation fault.
        if(endX > (int)curLay.size())    endX = (int)curLay.size();
        if(endY > (int)curLay[0].size()) endY = (int)curLay[0].size();
    }
}
