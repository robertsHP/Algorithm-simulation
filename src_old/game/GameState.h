#pragma once

#include "SFML/Graphics.hpp"

#include "GameData.h"
#include "State.h"
#include "Game.h"
#include "LevelHandler.h"

namespace RawEngine {
    class GameState : public State
    {
        public:
            GameState(EngineDataRef eData );
            virtual ~GameState () {}
            void init();
            void update(float deltaT);
            void draw(float deltaT);

            void ifKeyPressedEvent (sf::Event &ev);
            void ifKeyReleasedEvent (sf::Event &ev);
            void ifMousePressed(sf::Event& ev);
            void ifMouseReleased(sf::Event& ev);

            void heldControls ();
            void releasedHeldControls ();

            void pause () {}
            void resume () {}
        private:
            EngineDataRef eData;
            GameDataRef gData = std::make_shared<GameData>();

            std::map<sf::Keyboard::Key,bool> heldKeys;
            std::map<sf::Mouse::Button,bool> heldMouse;

            sf::Clock clock;
            sf::Sprite background;
            sf::Sprite tile;
    };
}
