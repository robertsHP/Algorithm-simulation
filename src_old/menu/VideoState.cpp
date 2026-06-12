#include "VideoState.h"
#include "VideoStateButtons.h"

namespace RawEngine {
    void VideoState::init(){
        sf::Vector2i winPos (GD_INPUT.correctPos(GD_WIN,sf::Vector2<int>(GD_WIN.getSize())));
        std::shared_ptr<ResChooser> rCh = std::make_shared<ResChooser>(
            eData,
            winPos.x/2-90,
            winPos.y/2-90,
            GD_CONFIG_ST->rot);

        this->menObj.clear();
        this->menObj.push_back(rCh);
        this->menObj.push_back(std::make_shared<BPPChooser>(
            eData,
            winPos.x/2-90,
            winPos.y/2-40,
            GD_CONFIG_ST->rot,
            rCh));
        this->menObj.push_back(std::make_shared<ScrnTButton>(
            eData,
            winPos.x/2-90,
            winPos.y/2+30,
            1,1,GD_CONFIG_ST->rot,
            "fullscreen"));
        this->menObj.push_back(std::make_shared<ScrnTButton>(
            eData,
            winPos.x/2-90,
            winPos.y/2+60,
            1,1,GD_CONFIG_ST->rot,
            "windowed"));
        this->menObj.push_back(std::make_shared<VideoExitButton>(
            eData,
            winPos.x/2-90,
            winPos.y/2+90,
            1,1,GD_CONFIG_ST->rot));
        this->menObj[0]->selected = true;
    }

    void VideoState::update(float deltaT)
    {
        std::size_t i;

        for(i = 0;i<this->menObj.size();++i){
            if(GD_INPUT.checkIfMouseWasMoved(GD_WIN))
                if(this->menObj[i]->objectHoveredOver(GD_INPUT.getCorrectMousePos(GD_WIN)))
                    GD_INPUT.nextWithMouse(i,this->menObj);
            this->menObj[i]->update(deltaT);
        }
    }

    void VideoState::draw(float deltaT)
    {
        GD_WIN.clear(sf::Color::Blue);

        std::size_t i;

        for(i = 0;i<this->menObj.size();++i){
            this->menObj[i]->draw(deltaT);
        }

        GD_WIN.display();
    }

////////////////////////INPUT//////////////////////////


    void VideoState::ifKeyPressedEvent (sf::Event &ev) {
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
    void VideoState::ifKeyReleasedEvent (sf::Event &ev) {
        GD_WIN.setKeyRepeatEnabled(true);
        std::size_t i;

        for(i = 0;i<this->menObj.size();++i){
            this->menObj[i]->ifKeyReleasedEvent(ev);
        }
    }
    void VideoState::ifMousePressed(sf::Event& ev){
        std::size_t i;

        for(i = 0;i<this->menObj.size();++i){
            this->menObj[i]->ifMousePressed(ev);
        }
    }
    void VideoState::ifMouseReleased(sf::Event& ev){
        std::size_t i;

        for(i = 0;i<this->menObj.size();++i){
            this->menObj[i]->ifMouseReleased(ev);
        }
    }
}
