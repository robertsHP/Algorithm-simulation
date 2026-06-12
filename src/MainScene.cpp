#include "MainScene.h"

#include "Texture.h"

#include <memory>

MainScene::MainScene() {
    Debug::log("INFO", "Loading scene.");

    // m_texture = std::make_shared<Engine::Texture>();
    // m_texture = new Engine::Texture(
    //     "../assets/MOUSE.png", (SDL_Point) {0, 0},
        
    // );

    // this->plainShader = std::make_unique<Engine::ShaderProgram>("textured");

    // this->texture = std::make_unique<Engine::Texture>(
    //     "../gfx/stonewall.png",
    //     GL_TEXTURE_2D,
    //     GL_TEXTURE0,
    //     GL_RGBA,
    //     GL_UNSIGNED_BYTE);
    // this->texture->texUnit(this->plainShader, "tex0", 0);

    // // Create the vertices for the mesh
    // std::vector<Engine::Vertex> vertices = {
    //     Engine::Vertex(glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
    //     Engine::Vertex(glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 0.0f)),
    //     Engine::Vertex(glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
    //     Engine::Vertex(glm::vec3(0.5f, 0.0f,  0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(5.0f, 0.0f)),
    //     Engine::Vertex(glm::vec3(0.0f, 0.5f,  0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(2.5f, 5.0f)),
    // };

    // // Define the indices for the mesh
    // std::vector<GLuint> indices = {
    //     0, 1, 2,
    //     0, 2, 3,
    //     0, 1, 4,
    //     1, 2, 4,
    //     2, 3, 4,
    //     3, 0, 4
    // };

    // // Create the mesh with the vectors
    // this->mesh = std::make_unique<Engine::Mesh>(vertices, indices);
}
MainScene::~MainScene() {
    Debug::log("INFO", "Closing scene.");
}

void MainScene::input () {
    
}
void MainScene::update (float deltaTime) {
    // this->mesh->update(deltaTime);



}
void MainScene::draw () {
    // this->mesh->draw(this->plainShader, this->texture);


    
}

