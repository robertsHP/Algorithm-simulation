#include "FileSelButton.h"

#include "MenuState.h"
#include "LevelHandler.h"

namespace RawEngine {
    FileSelButton::FileSelButton(EditorDataRef editData, EngineDataRef eData, float x, float y, float scaleX, float scaleY, float rot){
        this->eData = eData;
        this->editData = editData;
        this->sprite.setPosition(x,y);
        this->sprite.setScale(scaleX,scaleY);
        this->sprite.setRotation(rot);
        loadTextures();
        init();

        this->name = "File select button";
    }
    void FileSelButton::init() {
        float yPos = this->sprite.getPosition().y + this->sprite.getTexture()->getSize().y;

        this->objSt.push_back(std::make_shared<FileSaveBut>(
            editData,
            eData,
            0,
            yPos,
            1,1,GD_CONFIG_ST->rot));
        this->objSt.push_back(std::make_shared<FileLoadBut>(
            editData,
            eData,
            0,
            yPos * 2,
            1,1,GD_CONFIG_ST->rot));
        this->objSt.push_back(std::make_shared<FileExitBut>(
            editData,
            eData,
            0,
            yPos * 3,
            1,1,GD_CONFIG_ST->rot));
    }
    void FileSelButton::loadTextures() {
        GD_ASSETS.loadTexture("FILE_FILE",FILE_FILE);
        this->sprite.setTexture(GD_ASSETS.getTexture("FILE_FILE"));
    }
    bool FileSelButton::objectHoveredOver (sf::Vector2i mousePos) {
        sf::Vector2i spPos(this->sprite.getPosition());
        if(this->selected){
            for(std::size_t i = 0;i<this->objSt.size();++i){
                this->objSt[i]->objectHoveredOver(mousePos);
            }
        }
        return (getSpritePosCondition(
            mousePos,
            spPos,
            this->sprite.getTexture()->getSize().x,
            this->sprite.getTexture()->getSize().y)) ? true : false;
    }
    void FileSelButton::update (float deltaT) {
        if(this->selected) {
            this->sprite.setColor(sf::Color(this->r-50,this->g-50,this->b-50));

            for(std::size_t i = 0;i<this->objSt.size();++i){
                if(GD_INPUT.checkIfMouseWasMoved(GD_WIN)){
                    if(this->objSt[i]->objectHoveredOver(GD_INPUT.getCorrectMousePos(GD_WIN))){
                        GD_INPUT.nextWithMouse(i,this->objSt);
                    }
                }
                this->objSt[i]->update(deltaT);
            }
        } else if (!this->selected) {
            this->sprite.setColor(sf::Color(255,255,255));
        }
    }
    void FileSelButton::draw (float deltaT){
        GD_WIN.draw(this->sprite);
        if(this->selected) {
            for(std::size_t i = 0;i<this->objSt.size();++i){
                this->objSt[i]->draw(deltaT);
            }
        }
    }
    bool FileSelButton::ifKeyPressedEvent (sf::Event &ev) {
        for(std::size_t i = 0;i<this->objSt.size();++i){
            this->objSt[i]->ifKeyPressedEvent(ev);
        }
        return false;
    }
    bool FileSelButton::ifKeyReleasedEvent (sf::Event &ev){
        for(std::size_t i = 0;i<this->objSt.size();++i){
            this->objSt[i]->ifKeyReleasedEvent(ev);
        }
        return false;
    }

    bool FileSelButton::ifMousePressed (sf::Event &ev){
        if(this->selected) {
            for(std::size_t i = 0;i<this->objSt.size();++i){
                if(this->objSt[i]->ifMousePressed(ev))
                    return true;
            }
        }

        if(ev.mouseButton.button == sf::Mouse::Left){
            if(GD_INPUT.isSpriteClicked(this->sprite, GD_WIN)){
                if(this->selected){this->selected = false;}
                else if(!this->selected){this->selected = true;}
                return true;
            }
        }
        return false;
    }
    bool FileSelButton::ifMouseReleased (sf::Event &ev){
        if(this->selected) {
            for(std::size_t i = 0;i<this->objSt.size();++i){
                this->objSt[i]->ifMouseReleased(ev);
            }
        }
        return false;
    }

//////////////////CHILD BUTTON FUNCTIONS

    //////////////SAVE/////////////////

    FileSaveBut::FileSaveBut(EditorDataRef editData, EngineDataRef eData, float x, float y, float scaleX, float scaleY, float rot) {
        this->eData = eData;
        this->editData = editData;
        this->sprite.setPosition(x,y);
        this->sprite.setScale(scaleX,scaleY);
        this->sprite.setRotation(rot);
        loadTextures();

        this->name = "File save button";
    }
    void FileSaveBut::loadTextures() {
        GD_ASSETS.loadTexture("FILE_SAVE",FILE_SAVE);
        this->sprite.setTexture(GD_ASSETS.getTexture("FILE_SAVE"));
    }
    bool FileSaveBut::objectHoveredOver (sf::Vector2i mousePos) {
        sf::Vector2i spPos(this->sprite.getPosition());
        return (getSpritePosCondition(
            mousePos,
            spPos,
            this->sprite.getTexture()->getSize().x,
            this->sprite.getTexture()->getSize().y)) ? true : false;
    }
    void FileSaveBut::update (float deltaT) {
        if(this->selected) {
            this->sprite.setColor(sf::Color(this->r-50,this->g-50,this->b-50));
        } else if (!this->selected) {
            this->sprite.setColor(sf::Color(255,255,255));
        }
    }
    void FileSaveBut::draw (float deltaT){
        GD_WIN.draw(this->sprite);
    }
    bool FileSaveBut::ifKeyPressedEvent (sf::Event &ev) {return false;}
    bool FileSaveBut::ifKeyReleasedEvent (sf::Event &ev){return false;}

    bool FileSaveBut::ifMousePressed (sf::Event &ev){
        if(ev.mouseButton.button == sf::Mouse::Left){
            if(GD_INPUT.isSpriteClicked(this->sprite, GD_WIN)){
                lh::saveLevel(eData, editData->layers, editData->lvlName);
                return true;
            }
        }
        return false;
    }
    bool FileSaveBut::ifMouseReleased (sf::Event &ev){
        return false;
    }

    ////////////LOAD///////////////

    FileLoadBut::FileLoadBut(EditorDataRef editData, EngineDataRef eData, float x, float y, float scaleX, float scaleY, float rot) {
        this->eData = eData;
        this->editData = editData;
        this->sprite.setPosition(x,y);
        this->sprite.setScale(scaleX,scaleY);
        this->sprite.setRotation(rot);
        loadTextures();

        this->name = "File load button";
    }
    void FileLoadBut::loadTextures() {
        GD_ASSETS.loadTexture("FILE_LOAD",FILE_LOAD);
        this->sprite.setTexture(GD_ASSETS.getTexture("FILE_LOAD"));
    }
    bool FileLoadBut::objectHoveredOver (sf::Vector2i mousePos) {
        sf::Vector2i spPos(this->sprite.getPosition());
        return (getSpritePosCondition(
            mousePos,
            spPos,
            this->sprite.getTexture()->getSize().x,
            this->sprite.getTexture()->getSize().y)) ? true : false;
    }
    void FileLoadBut::update (float deltaT) {
        if(this->selected) {
            this->sprite.setColor(sf::Color(this->r-50,this->g-50,this->b-50));
        } else if (!this->selected) {
            this->sprite.setColor(sf::Color(255,255,255));
        }
    }
    void FileLoadBut::draw (float deltaT){
        GD_WIN.draw(this->sprite);
    }
    bool FileLoadBut::ifKeyPressedEvent (sf::Event &ev) {return false;}
    bool FileLoadBut::ifKeyReleasedEvent (sf::Event &ev){return false;}

    bool FileLoadBut::ifMousePressed (sf::Event &ev){
        if(ev.mouseButton.button == sf::Mouse::Left){
            if(GD_INPUT.isSpriteClicked(this->sprite, GD_WIN)){
                lh::loadLevel(eData, editData->layers, editData->lvlName);
                return true;
            }
        }
        return false;
    }
    bool FileLoadBut::ifMouseReleased (sf::Event &ev){
        return false;
    }

    //////////////////////EXIT/////////////

    FileExitBut::FileExitBut(EditorDataRef editData, EngineDataRef eData, float x, float y, float scaleX, float scaleY, float rot) {
        this->eData = eData;
        this->editData = editData;
        this->sprite.setPosition(x,y);
        this->sprite.setScale(scaleX,scaleY);
        this->sprite.setRotation(rot);
        loadTextures();

        this->name = "File exit button";
    }
    void FileExitBut::loadTextures() {
        GD_ASSETS.loadTexture("FILE_EXIT",FILE_EXIT);
        this->sprite.setTexture(GD_ASSETS.getTexture("FILE_EXIT"));
    }
    bool FileExitBut::objectHoveredOver (sf::Vector2i mousePos) {
        sf::Vector2i spPos(this->sprite.getPosition());
        return (getSpritePosCondition(
            mousePos,
            spPos,
            this->sprite.getTexture()->getSize().x,
            this->sprite.getTexture()->getSize().y)) ? true : false;
    }
    void FileExitBut::update (float deltaT) {
        if(this->selected) {
            this->sprite.setColor(sf::Color(this->r-50,this->g-50,this->b-50));
        } else if (!this->selected) {
            this->sprite.setColor(sf::Color(255,255,255));
        }
    }
    void FileExitBut::draw (float deltaT){
        GD_WIN.draw(this->sprite);
    }
    bool FileExitBut::ifKeyPressedEvent (sf::Event &ev) {return false;}
    bool FileExitBut::ifKeyReleasedEvent (sf::Event &ev){return false;}

    bool FileExitBut::ifMousePressed (sf::Event &ev){
        if(ev.mouseButton.button == sf::Mouse::Left){
            if(GD_INPUT.isSpriteClicked(this->sprite, GD_WIN)){
                eData->paused = false;
                GD_MACHINE.storedState.reset();
                GD_MACHINE.addState(StateRef(new MenuState(eData)));
                return true;
            }
        }
        return false;
    }
    bool FileExitBut::ifMouseReleased (sf::Event &ev){
        return false;
    }
}
