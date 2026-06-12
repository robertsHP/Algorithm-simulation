#include "LayerMenu.h"

namespace RawEngine {
/*
//////////////////////////////////////////////////////////////////////
//////////////////////////LAYER MENU//////////////////////////////////
//////////////////////////////////////////////////////////////////////
*/
        LayerMenu::LayerMenu(EditorDataRef editData, EngineDataRef eData) : eData(eData), editData(editData)
        {
            GD_ASSETS.loadAndSet("LM_MENU",LM_MENU,this->menu);
            init();
        }
        void LayerMenu::init () {
            sf::Color color;
            std::size_t i;

//            sf::Vector2u winSize (GD_INPUT.correctPos(GD_WIN,sf::Vector2<int>(GD_WIN.getSize())));
            this->menuSize = this->menu.getTexture()->getSize();
            this->menu.setPosition(0,50);

            this->layerCont.clear();

            for(i = 0; i < editData->layers.size(); ++i){
                this->layerCont.push_back(std::make_shared<LayerButton>(
                    editData,
                    eData,
                    "Layer "+std::to_string(i+1),
                    2, menu.getPosition().y + 16 + (29 * i),
                    1, 1, GD_CONFIG_ST->rot,
                    sf::Color(255,255,255),
                    &editData->layers[i]));
                if(i > 2)
                    this->layerCont[i]->changeEye();
            }
            this->layerCont[0]->selected = true;
        }
        void LayerMenu::update (float deltaT) {
            for(std::size_t i = 0; i < this->layerCont.size(); ++i){
                layerCont[i]->update(deltaT);
            }
        }
        void LayerMenu::draw(float deltaT){
            for(std::size_t i = 0; i < this->layerCont.size(); ++i){
                if(layerCont[i]->eyeOpen){
                    objH::drawLevelObjects(editData->drawGrid,eData,(*layerCont[i]->layer),deltaT);
                }
            }
            if(editData->dragSelInit){
                GD_WIN.draw(editData->dragSel);
            }

            GD_WIN.draw(this->menu);
            for(std::size_t i = 0; i < this->layerCont.size(); ++i){
                layerCont[i]->draw(deltaT);
            }
        }
        bool LayerMenu::ifKeyPressedEvent(sf::Event& ev) {
            return false;
        }

        bool LayerMenu::ifKeyReleasedEvent(sf::Event& ev) {
            return false;
        }

        bool LayerMenu::ifMousePressed(sf::Event& ev) {
            for(std::size_t i = 0; i < this->layerCont.size(); ++i){
                if(layerCont[i]->ifMousePressed(ev)) {
                    nextWithMouse(i, layerCont);
                    editData->selLayer = i;
                    return true;
                }
            }
            if(GD_INPUT.isSpriteClicked(this->menu, GD_WIN)){
                return true;
            }
            return false;
        }
        void LayerMenu::nextWithMouse (int index, LayBtnCont& menObjSt) {
            for(LayBtnCont::iterator it = menObjSt.begin();it != menObjSt.end();++it){
                if((*it)->selected){
                    (*it)->selected = false;
                }
            }
            menObjSt[index]->selected = true;
        }

        bool LayerMenu::ifMouseReleased(sf::Event& ev) {
            for(std::size_t i = 0;i<this->layerCont.size();++i){
                layerCont[i]->ifMouseReleased(ev);
            }
            return false;
        }
/*
//////////////////////////////////////////////////////////////////////
////////////////LAYER BUTTON//////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
*/
        LayerButton::LayerButton(EditorDataRef editData, EngineDataRef eData, std::string dispText,
                float x, float y, float scaleX, float scaleY, float rot, sf::Color color, Layer* layer) : layer(layer){
            this->eData = eData;
            this->editData = editData;
            this->sprite.setPosition(x,y);
            this->sprite.setScale(scaleX,scaleY);
            this->sprite.setRotation(rot);

            sf::Vector2f sprPos (this->sprite.getPosition());

            this->displayName.setFont(eData->font);
            this->displayName.setString(dispText);
            this->displayName.setCharacterSize(13);
            this->displayName.setFillColor(sf::Color::Black);
            this->displayName.setPosition(sprPos.x+5,sprPos.y+5);

            this->r = 255;
            this->g = 255;
            this->b = 255;

            this->eye.setPosition(x+89,y+6);
            this->eye.setScale(scaleX,scaleY);
            this->eye.setRotation(rot);

            loadTextures();

            this->name = dispText;
        }
        void LayerButton::changeEye () {
            if(this->eyeOpen){
                this->eye.setTexture(GD_ASSETS.getTexture("LM_EYE_CLOSED"));
                this->eyeOpen = false;
            } else {
                this->eye.setTexture(GD_ASSETS.getTexture("LM_EYE_OPEN"));
                this->eyeOpen = true;
            }
        }
        void LayerButton::loadTextures() {
            GD_ASSETS.loadAndSet("LM_BUTTON",LM_BUTTON,this->sprite);
            GD_ASSETS.loadTexture("LM_EYE_CLOSED",LM_EYE_CLOSED);
            GD_ASSETS.loadAndSet("LM_EYE_OPEN",LM_EYE_OPEN,this->eye);
        }
        bool LayerButton::objectHoveredOver (sf::Vector2i mousePos) {
            sf::Vector2i spPos(this->sprite.getPosition());
            return (getSpritePosCondition(
                mousePos,
                spPos,
                this->sprite.getTexture()->getSize().x,
                this->sprite.getTexture()->getSize().y)) ? true : false;
        }
        void LayerButton::update (float deltaT) {
            if(this->selected) {
                this->sprite.setColor(sf::Color(this->r-100,this->g-100,this->b-100));
            } else if (!selected) {
                this->sprite.setColor(sf::Color(255,255,255));
            }
        }
        void LayerButton::draw (float deltaT){
            GD_WIN.draw(this->sprite);
            GD_WIN.draw(this->displayName);
            GD_WIN.draw(this->eye);
        }
        bool LayerButton::ifKeyPressedEvent (sf::Event &ev) {
            return false;
        }
        bool LayerButton::ifKeyReleasedEvent (sf::Event &ev){
            return false;
        }

        bool LayerButton::ifMousePressed (sf::Event &ev){
            if(ev.mouseButton.button == sf::Mouse::Left){
                if(GD_INPUT.isSpriteClicked(this->eye, GD_WIN)){
                    changeEye();
                } else if(GD_INPUT.isSpriteClicked(this->sprite, GD_WIN)){
                    return true;
                }
            }
            return false;
        }
        bool LayerButton::ifMouseReleased (sf::Event &ev){
            return false;
        }
}
