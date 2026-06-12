#include "OptionState.h"
#include "OptionStateButtons.h"

namespace RawEngine {
    void OptionState::init()
    {
        sf::Vector2i winPos (GD_INPUT.correctPos(GD_WIN,sf::Vector2<int>(GD_WIN.getSize())));
        this->menObj.clear();
        this->menObj.push_back(std::make_shared<VideoButton>(
            eData,
            winPos.x/2-20,
            winPos.y/2-30,
            1,1,GD_CONFIG_ST->rot));
        this->menObj.push_back(std::make_shared<OptionExitButton>(
            eData,
            winPos.x/2-20,
            winPos.y/2,
            1,1,GD_CONFIG_ST->rot));
        this->menObj[0]->selected = true;
    }

    void OptionState::update(float deltaT){
        std::size_t i;

        for(i = 0;i<this->menObj.size();++i){
            if(GD_INPUT.checkIfMouseWasMoved(GD_WIN))
                if(this->menObj[i]->objectHoveredOver(GD_INPUT.getCorrectMousePos(GD_WIN)))
                    GD_INPUT.nextWithMouse(i,this->menObj);
            this->menObj[i]->update(deltaT);
        }
    }

    void OptionState::draw(float deltaT)
    {
        std::size_t i;

        GD_WIN.clear(sf::Color::Blue);

        for(i = 0;i<this->menObj.size();++i){
            this->menObj[i]->draw(deltaT);
        }

        GD_WIN.display();
    }

//////////////////////////////INPUT///////////////////////

    void OptionState::ifKeyPressedEvent(sf::Event& ev)
    {
        std::size_t i;

        for(i = 0;i<this->menObj.size();++i){
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
            default : break;
        }
    }

    void OptionState::ifKeyReleasedEvent(sf::Event& ev)
    {
        GD_WIN.setKeyRepeatEnabled(true);

        std::size_t i;

        for(i = 0;i<this->menObj.size();++i){
            this->menObj[i]->ifKeyReleasedEvent(ev);
        }
    }
    void OptionState::ifMousePressed(sf::Event& ev)
    {
        std::size_t i;
        for(i = 0;i<this->menObj.size();++i){
            this->menObj[i]->ifMousePressed(ev);
        }
    }

    void OptionState::ifMouseReleased(sf::Event& ev)
    {
        std::size_t i;
        for(i = 0;i<this->menObj.size();++i){
            this->menObj[i]->ifMouseReleased(ev);
        }
    }
}
