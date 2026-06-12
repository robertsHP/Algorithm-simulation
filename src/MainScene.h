#pragma once

#include "Debug.h"

#include "Engine.h"
#include "Input.h"

// #include "ShaderProgram.h"
#include "Texture.h"
// #include "Mesh.h"
// #include "Vertex.h"

class MainScene : public Scene {
    private :
        // std::shared_ptr<Engine::ShaderProgram> plainShader;
        // std::shared_ptr<Engine::Mesh> mesh;
        // std::shared_ptr<Engine::Texture> m_texture;
        Texture *m_texture;
    public:
        MainScene();
        ~MainScene();

        void input () override;
        void update (float deltaTime) override;
        void draw () override;
};

