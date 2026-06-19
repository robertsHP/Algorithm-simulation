#pragma once

#include <memory>
#include <vector>

#include "CellularAutomata.h"
#include "Debug.h"

// #include "Engine.h"
// #include "Input.h"

// // #include "ShaderProgram.h"
// #include "Texture.h"
// // #include "Mesh.h"
// // #include "Vertex.h"



// #include "Tile.h"
#include "TileMap.h"
#include "StateButton.h"


class MainScene : public Scene {
    public:

    //     enum SimState {
    //         START, STOP, RESET,
    //         COUNT
    //     };

        void setCurrentSimState (SimState state) { 
            m_currentState = state;
        }

    private :
        // std::shared_ptr<Engine::ShaderProgram> plainShader;
        // std::shared_ptr<Engine::Mesh> mesh;

        // std::unique_ptr<Tile> m_tile;

        TileMap *m_tileMap;
        CellularAutomata *m_celAutomata;

        StateButton *m_stateButtons [SimState::COUNT];

        SimState m_currentState;

    public:
        MainScene();
        ~MainScene() override;

        void loadStateButtons ();

        void input () override;
        void update (float deltaTime) override;
        void draw () override;
};

