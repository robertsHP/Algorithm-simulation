#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include "SDL.h"

class Input {
    public :
        std::vector<SDL_Event> keyEvents;
        std::vector<SDL_Event> mouseEvents;
        uint8_t *keyBoardState;
        uint32_t mouseState;

        void update ();
        bool ifCondApplyToKeyEventCont (uint32_t inputType, uint8_t scanCode, uint8_t repeatAmount);
        bool ifCondApplyToMouseEventCont (uint32_t inputType, uint8_t scanCode, uint8_t clickAmount);
        bool keyPressed (uint8_t scanCode);
        bool keyReleased (uint8_t scanCode);
        bool keyHeldDown (uint8_t scanCode);
        bool mousePressed (uint8_t scanCode);
        bool mouseReleased (uint8_t scanCode);
        bool mouseHeldDown (uint8_t mask);
};

#endif // INPUT_H
