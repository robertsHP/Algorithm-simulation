#pragma once

// #include "SFML/Graphics.hpp"



// #include "StateMachine.h"
// #include "AssetManager.h"
// #include "InputManager.h"
// #include "Config.h"

namespace RawEngine {
    // #ifndef GAME_SH
    //     #define GAME_SH
    //         #define GD_MACHINE eData->machine
    //         #define GD_WIN eData->window
    //         #define GD_VIEW eData->view
    //         #define GD_ASSETS eData->assets
    //         #define GD_INPUT eData->input
    //         #define GD_CONFIG eData->config
    //         #define GD_CONFIG_ST eData->config._cst
    //         #define GD_FONT eData->font
    //         #define GD_CURSOR eData->cursor
    // #endif // GAME_SHORTENED
    #ifndef CONFIG_SH
        #define CONFIG_SH
            // #define AVAILABLE_VIDEOMODES eData->config.modes
            #define TEXT_SIZE 25
            #define MAIN_FONT "assets/VT323-Regular.ttf"
            #define TILE_W 25
            #define TILE_H 25
            #define LAYER_AMOUNT 6
            #define SCRN_MOVE_VEL 7
    #endif // CONFIG_SHORTENED

    struct EngineData {
        StateMachine machine;
        sf::RenderWindow window;
        sf::View view;
        AssetManager assets;
        InputManager input;
        Config config;
        sf::Font font;
        sf::Cursor cursor;
        bool mCursorGrab;
        bool paused = false;
    };

    typedef std::shared_ptr<EngineData> EngineDataRef;

    class Game {
        public:
            Game();
        private :
            const float deltaT = 1.0f/60.0f;
            sf::Clock _clock;

            EngineDataRef eData = std::make_shared<EngineData>();

            void run ();
            void handleInput ();
    };

    void loadFont (EngineDataRef eData, std::string fileLoc);
    void additionalOpt (EngineDataRef eData);
    void createWindow (EngineDataRef eData);
    void gameCloseOperation(EngineDataRef eData);
}
