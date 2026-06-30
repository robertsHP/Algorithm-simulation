#include <iostream>
#include <fstream>
#include <string>

#include "SDL.h"
#include "SDL_image.h"

#include <memory>
#include <filesystem> 

#include "Engine.h"
#include "MainScene.h"

void printWorkingDir () {
    // finding and printing the current working directory.
    printf("Current path is %s\n", std::filesystem::current_path().c_str());
}

int main() {
    printWorkingDir();

    Engine &engine = Engine::getInstance();

    engine.init();
    engine.setCurrentScene(new MainScene());
    engine.startLoop();

    engine.kill();
}

