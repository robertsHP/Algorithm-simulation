#include "Input.h"
#include "Engine.h"

#include <algorithm>

void Input::update () {
    
    if(!mouseEvents.empty())
        Input::mouseEvents.clear();  ///!!!!maybe doesnt need to be checked
    if(!keyEvents.empty())
        keyEvents.clear();

    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch(event.type){
            case SDL_QUIT :
                Engine::getInstance().stopLoop();
//                  Engine::exitCond = 0;
//                  Engine::loopOn = false;
                return;
            case SDL_MOUSEBUTTONDOWN :
            case SDL_MOUSEBUTTONUP :
                mouseEvents.push_back(event);
                break;
            case SDL_KEYDOWN :
            case SDL_KEYUP :
                keyEvents.push_back(event);
                break;
            default : break;
        }
        event = {};
    }
    keyBoardState = (uint8_t*) SDL_GetKeyboardState(NULL);
//            mouseState = SDL_GetMouseState(&Cursor::rect.x, &Cursor::rect.y);
}
bool Input::ifCondApplyToKeyEventCont (uint32_t inputType, uint8_t scanCode, uint8_t repeatAmount) {
    return std::find_if(
        keyEvents.begin(),
        keyEvents.end(),
        [&inputType, &scanCode, &repeatAmount](const SDL_Event &event) {
            return event.type == inputType && event.key.repeat == repeatAmount && event.key.keysym.scancode == scanCode;
        }
    ) != std::end(keyEvents);
}
bool Input::ifCondApplyToMouseEventCont (uint32_t inputType, uint8_t scanCode, uint8_t clickAmount) {
    return std::find_if(
        mouseEvents.begin(),
        mouseEvents.end(),
        [&inputType, &scanCode, &clickAmount](const SDL_Event &event) {
            return event.type == inputType && event.button.clicks == clickAmount && event.button.button == scanCode;
        }
    ) != std::end(mouseEvents);
}
bool Input::keyPressed (uint8_t scanCode) {
    return ifCondApplyToKeyEventCont(SDL_KEYDOWN, scanCode, 0);
}
bool Input::keyReleased (uint8_t scanCode) {
    return ifCondApplyToKeyEventCont(SDL_KEYUP, scanCode, 0);
}
bool Input::keyHeldDown (uint8_t scanCode) {
    return keyBoardState[scanCode];
}
bool Input::mousePressed (uint8_t scanCode) {
    return ifCondApplyToMouseEventCont(SDL_MOUSEBUTTONDOWN, scanCode, 1);
}
bool Input::mouseReleased (uint8_t scanCode) {
    return ifCondApplyToMouseEventCont(SDL_MOUSEBUTTONUP, scanCode, 1);
}
bool Input::mouseHeldDown (uint8_t mask) {
    return (mouseState & mask) != 0;
}
