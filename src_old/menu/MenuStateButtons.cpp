#include "MenuStateButtons.h"

#include "EditorState.h"
#include "OptionState.h"
#include "game/GameState.h"

namespace RawEngine {

    //////////RESUME BUTTON//////////////

        ResumeButton::ResumeButton(EngineDataRef data, float x, float y, float scaleX, float scaleY, float rot) {
            this->eData = data;
            this->sprite.setPosition(x,y);
            this->sprite.setScale(scaleX,scaleY);
            this->sprite.setRotation(rot);
            loadTextures();

            this->name = "Resume button";
        }
        void ResumeButton::loadTextures() {
            GD_ASSETS.loadTexture("MENU_RESUME_BTN",MENU_RESUME_BTN);
            this->sprite.setTexture(GD_ASSETS.getTexture("MENU_RESUME_BTN"));
        }
        bool ResumeButton::objectHoveredOver (sf::Vector2i mousePos) {
            sf::Vector2i spPos(this->sprite.getPosition());
            return (getSpritePosCondition(
                mousePos,
                spPos,
                this->sprite.getTexture()->getSize().x,
                this->sprite.getTexture()->getSize().y)) ? true : false;
        }
        void ResumeButton::update (float deltaT) {
            if(this->selected) {
                glowAnimation(254,254,254);
                this->sprite.setColor(sf::Color(this->r,this->g,this->b));
            } else if (!selected && this->r != 255) {
                this->sprite.setColor(sf::Color(255,255,255));
            }
        }
        void ResumeButton::draw (float deltaT){
            GD_WIN.draw(this->sprite);
        }
        bool ResumeButton::ifKeyPressedEvent (sf::Event &ev) {
            GD_WIN.setKeyRepeatEnabled(false);
            if(this->selected){
                if(ev.key.code == sf::Keyboard::Enter){
                    if(eData->paused){
                        eData->paused = false;
                        GD_MACHINE.removeState();
                    }
                    return true;
                }
            }
            return false;
        }
        bool ResumeButton::ifKeyReleasedEvent (sf::Event &ev){
            GD_WIN.setKeyRepeatEnabled(true);
            return false;
        }
        bool ResumeButton::ifMousePressed (sf::Event &ev){
            if(ev.mouseButton.button == sf::Mouse::Left){
                if(GD_INPUT.isSpriteClicked(this->sprite, GD_WIN)){
                    if(eData->paused){
                        eData->paused = false;
                        GD_MACHINE.removeState();
                    }
                    return true;
                }
            }
            return false;
        }
        bool ResumeButton::ifMouseReleased (sf::Event &ev){
            return false;
        }

    //////////GAME STATE BUTTON//////////////

        GameButton::GameButton(EngineDataRef data, float x, float y, float scaleX, float scaleY, float rot) {
            this->eData = data;
            this->sprite.setPosition(x,y);
            this->sprite.setScale(scaleX,scaleY);
            this->sprite.setRotation(rot);
            loadTextures();

            this->name = "game btn";
        }
        void GameButton::loadTextures() {
            GD_ASSETS.loadTexture("MENU_GAME_BTN",MENU_GAME_BTN);
            this->sprite.setTexture(GD_ASSETS.getTexture("MENU_GAME_BTN"));
        }
        bool GameButton::objectHoveredOver (sf::Vector2i mousePos) {
            sf::Vector2i spPos(this->sprite.getPosition());
            return (getSpritePosCondition(
                mousePos,
                spPos,
                this->sprite.getTexture()->getSize().x,
                this->sprite.getTexture()->getSize().y)) ? true : false;
        }
        void GameButton::update (float deltaT) {
            if(this->selected) {
                glowAnimation(254,254,254);
                this->sprite.setColor(sf::Color(this->r,this->g,this->b));
            } else if (!selected && this->r != 255) {
                this->sprite.setColor(sf::Color(255,255,255));
            }
        }
        void GameButton::draw (float deltaT){
            GD_WIN.draw(this->sprite);
        }
        bool GameButton::ifKeyPressedEvent (sf::Event &ev) {
            GD_WIN.setKeyRepeatEnabled(false);
            if(this->selected){
                if(ev.key.code == sf::Keyboard::Enter){
                    GD_MACHINE.addState(StateRef(new GameState(eData)));
                    return true;
                }
            }
            return false;
        }
        bool GameButton::ifKeyReleasedEvent (sf::Event &ev){
            GD_WIN.setKeyRepeatEnabled(true);
            return false;
        }
        bool GameButton::ifMousePressed (sf::Event &ev){
            if(ev.mouseButton.button == sf::Mouse::Left){
                if(GD_INPUT.isSpriteClicked(this->sprite, GD_WIN)){
                    GD_MACHINE.addState(StateRef(new GameState(eData)));
                    return true;
                }
            }
            return false;
        }
        bool GameButton::ifMouseReleased (sf::Event &ev){
            return false;
        }

    //////////EDITOR STATE BUTTON//////////////

        EditorButton::EditorButton(EngineDataRef data, float x, float y, float scaleX, float scaleY, float rot) {
            this->eData = data;
            this->sprite.setPosition(x,y);
            this->sprite.setScale(scaleX,scaleY);
            this->sprite.setRotation(rot);
            loadTextures();

            this->name = "editor btn";
        }
        void EditorButton::loadTextures() {
            GD_ASSETS.loadTexture("MENU_EDITOR_BTN",MENU_EDITOR_BTN);
            this->sprite.setTexture(GD_ASSETS.getTexture("MENU_EDITOR_BTN"));
        }
        bool EditorButton::objectHoveredOver (sf::Vector2i mousePos) {
            sf::Vector2i spPos(this->sprite.getPosition());
            return (getSpritePosCondition(
                mousePos,
                spPos,
                this->sprite.getTexture()->getSize().x,
                this->sprite.getTexture()->getSize().y)) ? true : false;
        }
        void EditorButton::update (float deltaT) {
            if(this->selected) {
                glowAnimation(254,254,254);
                this->sprite.setColor(sf::Color(this->r,this->g,this->b));
            } else if (!selected && this->r != 255) {
                this->sprite.setColor(sf::Color(255,255,255));
            }
        }
        void EditorButton::draw (float deltaT){
            GD_WIN.draw(this->sprite);
        }
        bool EditorButton::ifKeyPressedEvent (sf::Event &ev) {
            GD_WIN.setKeyRepeatEnabled(false);
            if(this->selected){
                if(ev.key.code == sf::Keyboard::Enter){
                    GD_MACHINE.addState(StateRef(new EditorState(eData)));
                    return true;
                }
            }
            return false;
        }
        bool EditorButton::ifKeyReleasedEvent (sf::Event &ev){
            GD_WIN.setKeyRepeatEnabled(true);
            return false;
        }
        bool EditorButton::ifMousePressed (sf::Event &ev){
            if(ev.mouseButton.button == sf::Mouse::Left){
                if(GD_INPUT.isSpriteClicked(this->sprite, GD_WIN)){
                    GD_MACHINE.addState(StateRef(new EditorState(eData)));
                    return true;
                }
            }
            return false;
        }
        bool EditorButton::ifMouseReleased (sf::Event &ev){
            return false;
        }

    ////////OPTION STATE BUTTON/////////////

        OptionButton::OptionButton(EngineDataRef data, float x, float y, float scaleX, float scaleY, float rot) {
            this->eData = data;
            this->sprite.setPosition(x,y);
            this->sprite.setScale(scaleX,scaleY);
            this->sprite.setRotation(rot);
            loadTextures();

            this->name = "opt button";
        }
        bool OptionButton::objectHoveredOver (sf::Vector2i mousePos) {
            sf::Vector2i spPos(this->sprite.getPosition());
            return (getSpritePosCondition(
                mousePos,
                spPos,
                this->sprite.getTexture()->getSize().x,
                this->sprite.getTexture()->getSize().y)) ? true : false;
        }
        void OptionButton::loadTextures() {
            GD_ASSETS.loadTexture("MENU_OPT_BTN",MENU_OPT_BTN);
            this->sprite.setTexture(GD_ASSETS.getTexture("MENU_OPT_BTN"));
        }
        void OptionButton::update (float deltaT) {
            if(selected) {
                glowAnimation(254,254,254);
                this->sprite.setColor(sf::Color(this->r,this->g,this->b));
            } else if (!selected && this->sprite.getColor().r != 255) {
                this->sprite.setColor(sf::Color(255,255,255));
            }
        }
        void OptionButton::draw (float deltaT){
            GD_WIN.draw(this->sprite);
        }
        bool OptionButton::ifKeyPressedEvent (sf::Event &ev) {
            GD_WIN.setKeyRepeatEnabled(false);
            if(this->selected){
                if(ev.key.code == sf::Keyboard::Enter){
                    GD_MACHINE.addState(StateRef(new OptionState(this->eData)));
                    return true;
                }
            }
            return false;
        }
        bool OptionButton::ifKeyReleasedEvent (sf::Event &ev){
            GD_WIN.setKeyRepeatEnabled(true);
            return false;
        }
        bool OptionButton::ifMousePressed (sf::Event &ev){
            if(ev.mouseButton.button == sf::Mouse::Left){
                if(GD_INPUT.isSpriteClicked(this->sprite, GD_WIN)){
                    eData->machine.addState(StateRef(new OptionState(eData)));
                    return true;
                }
            }
            return false;
        }
        bool OptionButton::ifMouseReleased (sf::Event &ev){
            return false;
        }

    ///////////EXIT OUT OF GAME BUTTON////////////////

        ExitButton::ExitButton(EngineDataRef data, float x, float y, float scaleX, float scaleY, float rot) {
            this->eData = data;
            this->sprite.setPosition(x,y);
            this->sprite.setScale(scaleX,scaleY);
            this->sprite.setRotation(rot);
            loadTextures();

            this->name = "exit btn";
        }
        void ExitButton::loadTextures() {
            GD_ASSETS.loadTexture("MENU_EXIT_BTN",MENU_EXIT_BTN);
            this->sprite.setTexture(GD_ASSETS.getTexture("MENU_EXIT_BTN"));
        }
        bool ExitButton::objectHoveredOver (sf::Vector2i mousePos) {
            sf::Vector2i spPos(this->sprite.getPosition());
            return (getSpritePosCondition(
                mousePos,
                spPos,
                this->sprite.getTexture()->getSize().x,
                this->sprite.getTexture()->getSize().y)) ? true : false;
        }
        void ExitButton::update (float deltaT) {
            if(this->selected) {
                glowAnimation(254,254,254);
                this->sprite.setColor(sf::Color(this->r,this->g,this->b));
            } else if (!selected && this->r != 255) {
                this->sprite.setColor(sf::Color(255,255,255));
            }
        }
        void ExitButton::draw (float deltaT){
            GD_WIN.draw(this->sprite);
        }
        bool ExitButton::ifKeyPressedEvent (sf::Event &ev) {
            GD_WIN.setKeyRepeatEnabled(false);
            if(this->selected){
                if(ev.key.code == sf::Keyboard::Enter){
                    gameCloseOperation(eData);
                    return true;
                }
            }
            return false;
        }
        bool ExitButton::ifKeyReleasedEvent (sf::Event &ev){
            GD_WIN.setKeyRepeatEnabled(true);
            return false;
        }
        bool ExitButton::ifMousePressed (sf::Event &ev){
            if(ev.mouseButton.button == sf::Mouse::Left){
                if(GD_INPUT.isSpriteClicked(this->sprite, GD_WIN)){
                    gameCloseOperation(eData);
                    return true;
                }
            }
            return false;
        }
        bool ExitButton::ifMouseReleased (sf::Event &ev){
            return false;
        }
}
