#include "Game.h"
// #include "MenuState.h"

namespace RawEngine {
    Game::Game()
    {
        eData->mCursorGrab = true;
        loadFont(eData,MAIN_FONT);

        GD_CONFIG.readCFile();
        GD_VIEW.reset(sf::FloatRect(0,0,800,600));
        createWindow(eData);
        GD_MACHINE.addState(StateRef(new MenuState(eData)));

        this->run();
    }

    void Game::run()
    {
        float newTime,frameTime,interplotation;

        float currentTime = this->_clock.getElapsedTime().asSeconds();
        float accumulator = 0.0f;

        while(eData->window.isOpen()) {
            GD_MACHINE.processStateChanges();

            newTime = this->_clock.getElapsedTime().asSeconds();
            frameTime = newTime - currentTime;

            if(frameTime > 0.25f) {
                frameTime = 0.25f;
            }

            currentTime = newTime;
            accumulator += frameTime;

            while(accumulator >= deltaT) {
                handleInput();
                GD_MACHINE.getActiveState()->update(deltaT);
                accumulator -= deltaT;
            }

            interplotation = accumulator/deltaT;
            GD_MACHINE.getActiveState()->draw(interplotation);
        }
    }
    void Game::handleInput()
    {
        sf::Event event;
        StateRef curState (GD_MACHINE.getActiveState());

        if(eData->mCursorGrab){
            while(GD_WIN.pollEvent(event)){
                switch (event.type) {
                    case sf::Event::Closed :
                        gameCloseOperation(eData);
                        break;
                    case sf::Event::KeyPressed :
                        if(event.key.code == sf::Keyboard::LSystem){
                            eData->mCursorGrab = false;
                            GD_WIN.setMouseCursorGrabbed(false);
                        }
                        curState->ifKeyPressedEvent(event);
                        break;
                    case sf::Event::KeyReleased :
                        curState->ifKeyReleasedEvent(event);
                        break;
                    case sf::Event::MouseButtonPressed :
                        curState->ifMousePressed(event);
                        break;
                    case sf::Event::MouseButtonReleased :
                        curState->ifMouseReleased(event);
                        break;
                    default :
                        break;
                }
            }
        } else {
            while(GD_WIN.pollEvent(event)){
                switch (event.type) {
                    case sf::Event::Closed :
                        gameCloseOperation(eData);
                        break;
                    case sf::Event::MouseButtonPressed :
                        eData->mCursorGrab = true;
                        GD_WIN.setMouseCursorGrabbed(true);
                        break;
                    default :
                        break;
                }
            }
        }
    }
    void loadFont (EngineDataRef eData, std::string fileLoc) {
        if(!eData->font.loadFromFile(fileLoc)){
            printf("Failed to load font %s\n",fileLoc.c_str());
            return;
        }
    }
    void additionalOpt (EngineDataRef eData) {
        GD_WIN.setView(eData->view);
        (eData->mCursorGrab) ? GD_WIN.setMouseCursorGrabbed(true) : GD_WIN.setMouseCursorGrabbed(false);
    }
    void createWindow (EngineDataRef eData) {
        if(GD_CONFIG_ST->fullScr){
            GD_WIN.create(
                GD_CONFIG_ST->res,
                GD_CONFIG_ST->title,
                sf::Style::Fullscreen
            );
            additionalOpt(eData);
        } else {
            GD_WIN.create(
                GD_CONFIG_ST->res,
                GD_CONFIG_ST->title,
                sf::Style::Close | sf::Style::Titlebar
            );
            additionalOpt(eData);
        }
    }

    void gameCloseOperation (EngineDataRef eData) {
        GD_CONFIG.writeToCFile();
        GD_WIN.close();
    }
}
