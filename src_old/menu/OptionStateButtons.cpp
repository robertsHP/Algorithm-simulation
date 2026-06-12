#include "OptionStateButtons.h"

#include "MenuState.h"
#include "VideoState.h"

namespace RawEngine {
    //////////VIDEO STATE BUTTON//////////
        VideoButton::VideoButton(EngineDataRef data, float x, float y, float scaleX, float scaleY, float rot) {
            this->eData = data;
            this->sprite.setPosition(x,y);
            this->sprite.setScale(scaleX,scaleY);
            this->sprite.setRotation(rot);
            loadTextures();

            this->name = "video btn";
        }
        bool VideoButton::objectHoveredOver (sf::Vector2i mousePos) {
            sf::Vector2i spPos(this->sprite.getPosition());
            return (getSpritePosCondition(
                mousePos,spPos,
                this->sprite.getTexture()->getSize().x,
                this->sprite.getTexture()->getSize().y)) ? true : false;
        }

        void VideoButton::loadTextures() {
            GD_ASSETS.loadTexture("BTN_SCRN",BTN_SCRN);
            this->sprite.setTexture(GD_ASSETS.getTexture("BTN_SCRN"));
        }
        void VideoButton::update (float deltaT) {
            if(selected) {
                glowAnimation(254,254,254);
                this->sprite.setColor(sf::Color(this->r,this->g,this->b));
            } else if (!selected && this->sprite.getColor().r != 255) {
                this->sprite.setColor(sf::Color(255,255,255));
            }
        }
        void VideoButton::draw (float deltaT){
            GD_WIN.draw(this->sprite);
        }
        bool VideoButton::ifKeyPressedEvent (sf::Event &ev) {
            GD_WIN.setKeyRepeatEnabled(false);
            if(this->selected){
                if(ev.key.code == sf::Keyboard::Enter){
                    GD_MACHINE.addState(StateRef(new VideoState(eData)));
                    return true;
                }
            }
            return false;
        }
        bool VideoButton::ifKeyReleasedEvent (sf::Event &ev){
            GD_WIN.setKeyRepeatEnabled(true);
            return false;
        }
        bool VideoButton::ifMousePressed (sf::Event &ev){
            if(ev.mouseButton.button == sf::Mouse::Left){
                if(GD_INPUT.isSpriteClicked(this->sprite, GD_WIN)){
                    eData->machine.addState(StateRef(new VideoState(eData)));
                    return true;
                }
            }
            return false;
        }
        bool VideoButton::ifMouseReleased (sf::Event &ev){
            return false;
        }
    //////////OPTION EXIT BUTTON////////////
        OptionExitButton::OptionExitButton(EngineDataRef data, float x, float y, float scaleX, float scaleY, float rot) {
            this->eData = data;
            this->sprite.setPosition(x,y);
            this->sprite.setScale(scaleX,scaleY);
            this->sprite.setRotation(rot);
            loadTextures();

            this->name = "option exit btn";
        }
        void OptionExitButton::loadTextures() {
            GD_ASSETS.loadTexture("BTN_BACK",BTN_BACK);
            this->sprite.setTexture(GD_ASSETS.getTexture("BTN_BACK"));
        }
        bool OptionExitButton::objectHoveredOver (sf::Vector2i mousePos) {
            sf::Vector2i spPos(this->sprite.getPosition());
            return (getSpritePosCondition(
                mousePos,
                spPos,
                this->sprite.getTexture()->getSize().x,
                this->sprite.getTexture()->getSize().y)) ? true : false;
        }
        void OptionExitButton::update (float deltaT) {
            if(this->selected) {
                glowAnimation(254,254,254);
                this->sprite.setColor(sf::Color(this->r,this->g,this->b));
            } else if (!selected && this->r != 255) {
                this->sprite.setColor(sf::Color(255,255,255));
            }
        }
        void OptionExitButton::draw (float deltaT){
            GD_WIN.draw(this->sprite);
        }
        bool OptionExitButton::ifKeyPressedEvent (sf::Event &ev) {
            GD_WIN.setKeyRepeatEnabled(false);
            if(this->selected){
                if(ev.key.code == sf::Keyboard::Enter){
                    GD_MACHINE.addState(StateRef(new MenuState(eData)));
                    return true;
                }
            }
            if(ev.key.code == sf::Keyboard::Escape) {
                GD_MACHINE.addState(StateRef(new MenuState(eData)));
                return true;
            }
            return false;
        }
        bool OptionExitButton::ifKeyReleasedEvent (sf::Event &ev){
            GD_WIN.setKeyRepeatEnabled(true);
            return false;
        }
        bool OptionExitButton::ifMousePressed (sf::Event &ev){
            if(ev.mouseButton.button == sf::Mouse::Left){
                if(GD_INPUT.isSpriteClicked(this->sprite, GD_WIN)){
                    GD_MACHINE.addState(StateRef(new MenuState(eData)));
                    return true;
                }
            }
            return false;
        }
        bool OptionExitButton::ifMouseReleased (sf::Event &ev){
            return false;
        }
}
