#include <iostream>

#include "MenuState.h"
#include "MenuStateButtons.h"

namespace RawEngine {
    MenuState::MenuState(EngineDataRef eData) : eData(eData) {}

    void MenuState::init()
    {
        sf::Vector2i winPos (GD_INPUT.correctPos(GD_WIN,sf::Vector2<int>(GD_WIN.getSize())));
        this->menObj.clear();
        if(eData->paused){
            this->menObj.push_back(std::make_shared<ResumeButton>(
                eData,
                winPos.x/2-100,
                winPos.y/2-210,
                1,1,GD_CONFIG_ST->rot));
        }
        this->menObj.push_back(std::make_shared<GameButton>(
            eData,
            winPos.x/2-100,
            winPos.y/2-180,
            1,1,GD_CONFIG_ST->rot));
        this->menObj.push_back(std::make_shared<EditorButton>(
            eData,
            winPos.x/2-100,
            winPos.y/2-150,
            1,1,GD_CONFIG_ST->rot));
        this->menObj.push_back(std::make_shared<OptionButton>(
            eData,
            winPos.x/2-100,
            winPos.y/2-120,
            1,1,GD_CONFIG_ST->rot));
        this->menObj.push_back(std::make_shared<ExitButton>(
            eData,
            winPos.x/2-100,
            winPos.y/2-90,
            1,1,GD_CONFIG_ST->rot));
        this->menObj[0]->selected = true;
    }

    void MenuState::update(float deltaT)
    {
        for(std::size_t i = 0;i<this->menObj.size();++i){
            if(GD_INPUT.checkIfMouseWasMoved(GD_WIN)){
                if(this->menObj[i]->objectHoveredOver(GD_INPUT.getCorrectMousePos(GD_WIN))){
                    GD_INPUT.nextWithMouse(i,this->menObj);
                }
            }
            this->menObj[i]->update(deltaT);
        }
    }

    void MenuState::draw(float deltaT)
    {
        GD_WIN.clear(sf::Color::Blue);

        for(std::size_t i = 0; i < this->menObj.size(); ++i){
            this->menObj[i]->draw(deltaT);
        }

        GD_WIN.display();
    }

////////////////////////////INPUT//////////////////////

    void MenuState::ifKeyPressedEvent (sf::Event &ev) {
        for(std::size_t i = 0; i < this->menObj.size(); ++i){
            this->menObj[i]->ifKeyPressedEvent(ev);
        }

        //UP DOWN CONTROLS
        GD_WIN.setKeyRepeatEnabled(false);

        switch(ev.key.code){
            case sf::Keyboard::Up :
                GD_INPUT.nextButton(true,this->menObj);
                break;
            case sf::Keyboard::Down :
                GD_INPUT.nextButton(false,this->menObj);
                break;
            case sf::Keyboard::Escape :
                if(eData->paused){
                    eData->paused = false;
                    GD_MACHINE.removeState();
                }
                break;
            default : break;
        }
    }
    void MenuState::ifKeyReleasedEvent (sf::Event &ev) {
        GD_WIN.setKeyRepeatEnabled(true);
        for(std::size_t i = 0; i < this->menObj.size(); ++i){
            this->menObj[i]->ifKeyReleasedEvent(ev);
        }
    }
    void MenuState::ifMousePressed(sf::Event& ev){
        for(std::size_t i = 0; i < this->menObj.size(); ++i){
            this->menObj[i]->ifMousePressed(ev);
        }
    }
    void MenuState::ifMouseReleased(sf::Event& ev){
        for(std::size_t i = 0; i < this->menObj.size(); ++i){
            this->menObj[i]->ifMouseReleased(ev);
        }
    }
}
