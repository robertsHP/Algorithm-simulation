#include "VideoStateButtons.h"

#include "VarOperator.h"
#include "VideoState.h"
#include "OptionState.h"

namespace RawEngine {

///////////////////////BITS PER PIXEL CHOOSER////////////////////
        void BPPChooser::updateText (float x, float y) {
            this->text.setString(std::to_string(this->GD_CONFIG_ST->bpp));
            this->text.setCharacterSize(TEXT_SIZE);
            this->text.setFillColor(sf::Color::Black);
            this->text.setPosition(x + this->left.getTexture()->getSize().x+5+4,y+5+4);
        }
        BPPChooser::BPPChooser(EngineDataRef data, float x, float y, float rot, ResChPtr resCh) : eData(data), resCh(resCh)
        {
            this->xPos = x;
            this->yPos = y;
            this->rot = rot;

            for(VCont::iterator mode = AVAILABLE_VIDEOMODES.begin(); mode != AVAILABLE_VIDEOMODES.end(); ++mode){
                if(mode->bitsPerPixel > 0) {
                    printf("%s and bpp = %s\n",VarOp::resAsString((*mode)).c_str(),std::to_string(mode->bitsPerPixel).c_str());
                    bool storExists = false;

                    for(VSStorage::iterator vsStor = this->vsStor.begin(); vsStor != this->vsStor.end(); ++vsStor){
                        if(vsStor->bpp == mode->bitsPerPixel) {
                            vsStor->cont.push_back((*mode));
                            storExists = true;
                            break;
                        }
                    }
                    if(!storExists) {
                        VideoStorage vStor;
                        vStor.bpp = mode->bitsPerPixel;
                        vStor.cont.push_back((*mode));
                        this->vsStor.push_back(vStor);
                    }
                }
            }
            for(VSStorage::iterator vsStor = this->vsStor.begin(); vsStor != this->vsStor.end(); ++vsStor){
                if(vsStor->bpp == GD_CONFIG_ST->bpp) {
                    this->resCh->_modes = std::make_shared<VCont>(vsStor->cont);
                    break;
                }
            }
            GD_ASSETS.loadAndSet("BTN_CHOOSER_BG",BTN_CHOOSER_BG,this->bg);
            this->bg.setPosition(x,y);

            GD_ASSETS.loadAndSet("BTN_LEFT",BTN_LEFT,this->left);
            this->left.setPosition(x+4,y+4);

            this->text.setFont(this->GD_FONT);
            updateText(x,y);

            GD_ASSETS.loadAndSet("BTN_RIGHT",BTN_RIGHT,this->right);
            this->right.setPosition(x+this->right.getTexture()->getSize().x+110+4,y+4);

            this->name = "bpp chooser";
        }
        void BPPChooser::update (float deltaT) {
            if(selected) {
                glowAnimation(254,254,254);
                this->left.setColor(sf::Color(this->r,this->g,this->b));
                this->right.setColor(sf::Color(this->r,this->g,this->b));
                this->text.setFillColor(sf::Color(this->r,this->g,this->b));
            } else if (!selected && this->left.getColor().r != 255) {
                this->left.setColor(sf::Color(255,255,255));
                this->right.setColor(sf::Color(255,255,255));
                this->text.setFillColor(sf::Color(255,255,255));
            }
        }
        void BPPChooser::draw (float deltaT){
            GD_WIN.draw(this->bg);
            GD_WIN.draw(this->left);
            GD_WIN.draw(this->right);
            GD_WIN.draw(this->text);
        }

        bool BPPChooser::objectHoveredOver (sf::Vector2i mousePos) {
            sf::Vector2i pos(this->bg.getPosition());
                float xSize = this->bg.getTexture()->getSize().x;
                float ySize = this->bg.getTexture()->getSize().y;

            return (getSpritePosCondition(mousePos,pos,xSize,ySize)) ? true : false;
        }

        void BPPChooser::checkNextType(VSStorage::iterator& vsSt, NextBpp next){
            VSStorage::iterator newVSSt = next(vsSt,1);
            this->text.setString(std::to_string(newVSSt->bpp));

            this->resCh->setText(VarOp::resAsString(newVSSt->cont.at(0)));

            this->resCh->_modes = std::make_shared<VCont>(newVSSt->cont);
        }
        void BPPChooser::previousValue() {
            std::size_t i = 0;
            for(VSStorage::iterator storage = this->vsStor.begin(); storage != this->vsStor.end(); ++storage, ++i){
                if(std::to_string(storage->bpp) == this->text.getString()){
                    if(i == 0) break;
                    checkNextType(storage,&std::prev);
                }
            }
        }
        void BPPChooser::nextValue() {
            std::size_t i = this->vsStor.size();
            for(VSStorage::iterator storage = this->vsStor.end(); storage != this->vsStor.begin(); --storage, --i){
                if(std::to_string(storage->bpp) == this->text.getString()){
                    if(i == this->vsStor.size()) break;
                    checkNextType(storage,&std::next);
                }
            }
        }
        bool BPPChooser::ifKeyPressedEvent (sf::Event &ev) {
            if(selected) {
                if(ev.key.code == sf::Keyboard::Left){
                    nextValue();
                    return true;
                } else if (ev.key.code == sf::Keyboard::Right) {
                    previousValue();
                    return true;
                }
            }
            return false;
        }
        bool BPPChooser::ifKeyReleasedEvent (sf::Event &ev){
            GD_WIN.setKeyRepeatEnabled(true);
            return false;
        }
        bool BPPChooser::ifMousePressed (sf::Event &ev){
            if(GD_INPUT.isSpriteClicked(this->left, GD_WIN)){
                nextValue();
                return true;
            } else if (GD_INPUT.isSpriteClicked(this->right, GD_WIN)) {
                previousValue();
                return true;
            }
            return false;
        }
        bool BPPChooser::ifMouseReleased (sf::Event &ev){
            return false;
        }

/////////////////////////RESOLUTION CHOOSER/////////////////////////////////

        void ResChooser::updateText (float x, float y) {
            this->text.setString(VarOp::resAsString(this->GD_CONFIG_ST->res));
            this->text.setCharacterSize(TEXT_SIZE);
            this->text.setFillColor(sf::Color::Black);
            this->text.setPosition(x+this->left.getTexture()->getSize().x+5+4,y+5+4);
        }
        ResChooser::ResChooser(EngineDataRef data, float x, float y, float rot) : eData(data)
        {
            this->xPos = x;
            this->yPos = y;
            this->rot = rot;

            GD_ASSETS.loadAndSet("BTN_CHOOSER_BG",BTN_CHOOSER_BG,this->bg);
            this->bg.setPosition(x,y);

            GD_ASSETS.loadAndSet("BTN_LEFT",BTN_LEFT,this->left);
            this->left.setPosition(x+4,y+4);

            this->text.setFont(this->GD_FONT);
            updateText(x,y);

            GD_ASSETS.loadAndSet("BTN_RIGHT",BTN_RIGHT,this->right);
            this->right.setPosition(x+this->right.getTexture()->getSize().x+110+4,y+4);

            this->name = "res choose";
        }
        void ResChooser::update (float deltaT) {
            if(selected) {
                glowAnimation(254,254,254);
                this->left.setColor(sf::Color(this->r,this->g,this->b));
                this->right.setColor(sf::Color(this->r,this->g,this->b));
                this->text.setFillColor(sf::Color(this->r,this->g,this->b));
            } else if (!selected && this->left.getColor().r != 255) {
                this->left.setColor(sf::Color(255,255,255));
                this->right.setColor(sf::Color(255,255,255));
                this->text.setFillColor(sf::Color(255,255,255));
            }
        }
        void ResChooser::draw (float deltaT){
            GD_WIN.draw(this->bg);
            GD_WIN.draw(this->left);
            GD_WIN.draw(this->right);
            GD_WIN.draw(this->text);
        }

        bool ResChooser::objectHoveredOver (sf::Vector2i mousePos) {
            sf::Vector2i pos(this->bg.getPosition());
                float xSize = this->bg.getTexture()->getSize().x;
                float ySize = this->bg.getTexture()->getSize().y;

            return (getSpritePosCondition(mousePos,pos,xSize,ySize)) ? true : false;
        }

        void ResChooser::checkNextType(VCont::iterator& mode, Next next){
            VCont::iterator vm = next(mode,1);
            if(vm->width > 320 && vm->height > 200 && vm->width < 15360 && vm->height < 8640){
                std::string nextName = std::to_string(vm->width)+"x"+std::to_string(vm->height);
                this->text.setString(nextName);
            }
        }
        void ResChooser::previousValue () {
            std::size_t i = 0;
            for(VCont::iterator mode = this->_modes->begin(); mode < this->_modes->end()+1; ++mode, ++i){
                std::string curName = VarOp::resAsString((*mode));
                if(curName == this->text.getString()){
                    if(i == 0) break;
                    checkNextType(mode,&std::prev);
                }
            }
        }
        void ResChooser::nextValue () {
            std::size_t i = this->_modes->size();
            for(VCont::iterator mode = this->_modes->end(); mode > this->_modes->begin()-1; --mode, --i){
                std::string curName = VarOp::resAsString((*mode));
                if(curName == this->text.getString()){
                    if(i == this->_modes->size()) break;
                    checkNextType(mode,&std::next);
                }
            }
        }

        bool ResChooser::ifKeyPressedEvent (sf::Event &ev) {
            if(selected) {
                if(ev.key.code == sf::Keyboard::Left){
                    nextValue();
                    return true;
                } else if (ev.key.code == sf::Keyboard::Right) {
                    previousValue();
                    return true;
                }
                this->GD_WIN.setKeyRepeatEnabled(false);
                if (ev.key.code == sf::Keyboard::Enter) {
                    for(VCont::iterator mode = (*this->_modes).begin(); mode < (*this->_modes).end()+1; ++mode){
                        std::string vmName = VarOp::resAsString((*mode));
                        if(vmName == this->text.getString()){
                            printf("SETTING AS VIDEO MODE -> %s\n",vmName.c_str());
                            GD_CONFIG_ST->res = (*mode);
                            createWindow(eData);
                        }
                    }
                    return true;
                }
            }
            return false;
        }
        bool ResChooser::ifKeyReleasedEvent (sf::Event &ev){
            GD_WIN.setKeyRepeatEnabled(true);
            return false;
        }
        bool ResChooser::ifMousePressed (sf::Event &ev){
            if(GD_INPUT.isSpriteClicked(this->left, GD_WIN)){
                nextValue();
                return true;
            } else if (GD_INPUT.isSpriteClicked(this->right, GD_WIN)) {
                previousValue();
                return true;
            }
            return false;
        }
        bool ResChooser::ifMouseReleased (sf::Event &ev){
            return false;
        }

///////////////////////SCREEN CONDITION BUTTON (FULLSCREEN OR WINDOWED)/////////////

        ScrnTButton::ScrnTButton(EngineDataRef data, float x, float y, float scaleX, float scaleY, float rot, std::string name) {
            this->eData = data;
            this->sprite.setPosition(x,y);
            this->sprite.setScale(scaleX,scaleY);
            this->sprite.setRotation(rot);
            this->name = name;
            loadTextures(name);
        }
        bool ScrnTButton::objectHoveredOver (sf::Vector2i mousePos) {
            sf::Vector2i spPos(this->sprite.getPosition());
            return (getSpritePosCondition(
                mousePos,
                spPos,
                this->sprite.getTexture()->getSize().x,
                this->sprite.getTexture()->getSize().y)) ? true : false;
        }

        void ScrnTButton::loadTextures(std::string name) {
            if (name=="fullscreen") {
                GD_ASSETS.loadAndSet("BTN_FULLSCR",BTN_FULLSCR,this->sprite);
                this->butFullScr = true;
            } else if (name=="windowed") {
                GD_ASSETS.loadAndSet("BTN_WINDOWED",BTN_WINDOWED,this->sprite);
                this->butFullScr = false;
            }
        }
        void ScrnTButton::update (float deltaT) {
            if(selected) {
                glowAnimation(254,254,254);
                this->sprite.setColor(sf::Color(this->r,this->g,this->b));
            } else if (!selected && this->sprite.getColor().r != 255) {
                this->sprite.setColor(sf::Color(255,255,255));
            }
        }
        void ScrnTButton::draw (float deltaT){
            GD_WIN.draw(this->sprite);
        }
    ////////////////////////ACTION
        void ScrnTButton::performNewWindowAction () {
                if(!GD_CONFIG_ST->fullScr && this->butFullScr){
                    GD_WIN.create(
                        GD_CONFIG_ST->res,
                        GD_CONFIG_ST->title,
                        sf::Style::Fullscreen);
                    GD_WIN.setView(this->GD_VIEW);
                    GD_CONFIG_ST->fullScr = true;
                } else {
                    GD_WIN.create(
                        GD_CONFIG_ST->res,
                        GD_CONFIG_ST->title,
                        sf::Style::Close | sf::Style::Titlebar);
                    GD_WIN.setView(this->GD_VIEW);
                    GD_CONFIG_ST->fullScr = false;
                }
                this->GD_MACHINE.getActiveState()->init();
        }
    ///////////////////////
        bool ScrnTButton::ifKeyPressedEvent (sf::Event &ev) {
            GD_WIN.setKeyRepeatEnabled(false);
            if(this->selected){
                if(ev.key.code == sf::Keyboard::Enter){
                    performNewWindowAction();
                    return true;
                }
            }
            return false;
        }
        bool ScrnTButton::ifKeyReleasedEvent (sf::Event &ev){
            GD_WIN.setKeyRepeatEnabled(true);
            return false;
        }
        bool ScrnTButton::ifMousePressed (sf::Event &ev){
            if(ev.mouseButton.button == sf::Mouse::Left){
                if(GD_INPUT.isSpriteClicked(this->sprite, GD_WIN)){
                    performNewWindowAction();
                    return true;
                }
            }
            return false;
        }
        bool ScrnTButton::ifMouseReleased (sf::Event &ev){
            return false;
        }

    //////////VIDEO OPTION STATE EXIT BUTTON///////////////

        VideoExitButton::VideoExitButton(EngineDataRef data, float x, float y, float scaleX, float scaleY, float rot) {
            this->eData = data;
            this->sprite.setPosition(x,y);
            this->sprite.setScale(scaleX,scaleY);
            this->sprite.setRotation(rot);
            loadTextures();

            this->name = "option exit btn";
        }
        void VideoExitButton::loadTextures() {
            GD_ASSETS.loadTexture("BTN_BACK",BTN_BACK);
            this->sprite.setTexture(GD_ASSETS.getTexture("BTN_BACK"));
        }
        bool VideoExitButton::objectHoveredOver (sf::Vector2i mousePos) {
            sf::Vector2i spPos(this->sprite.getPosition());
            return (getSpritePosCondition(
                mousePos,
                spPos,
                this->sprite.getTexture()->getSize().x,
                this->sprite.getTexture()->getSize().y)) ? true : false;
        }
        void VideoExitButton::update (float deltaT) {
            if(this->selected) {
                glowAnimation(254,254,254);
                this->sprite.setColor(sf::Color(this->r,this->g,this->b));
            } else if (!selected && this->r != 255) {
                this->sprite.setColor(sf::Color(255,255,255));
            }
        }
        void VideoExitButton::draw (float deltaT){
            GD_WIN.draw(this->sprite);
        }
        bool VideoExitButton::ifKeyPressedEvent (sf::Event &ev) {
            GD_WIN.setKeyRepeatEnabled(false);
            if(this->selected){
                if(ev.key.code == sf::Keyboard::Enter){
                    GD_MACHINE.addState(StateRef(new OptionState(eData)));
                    return true;
                }
            }
            if(ev.key.code == sf::Keyboard::Escape) {
                eData->machine.addState(StateRef(new OptionState(eData)));
                return true;
            }
            return false;
        }
        bool VideoExitButton::ifKeyReleasedEvent (sf::Event &ev){
            GD_WIN.setKeyRepeatEnabled(true);
            return false;
        }
        bool VideoExitButton::ifMousePressed (sf::Event &ev){
            if(ev.mouseButton.button == sf::Mouse::Left){
                if(GD_INPUT.isSpriteClicked(this->sprite, GD_WIN)){
                    eData->machine.addState(StateRef(new OptionState(eData)));
                    return true;
                }
            }
            return false;
        }
        bool VideoExitButton::ifMouseReleased (sf::Event &ev){
            return false;
        }
}
