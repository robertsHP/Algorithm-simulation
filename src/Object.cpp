#include "Object.h"


Object::Object () {

}

Object::~Object () {

}

bool Object::ifHoveredOver () {
    bool hoverX, hoverY;
    int mouseX, mouseY;

    SDL_GetMouseState(&mouseX, &mouseY);

    hoverX = m_x < mouseX && (m_x + m_w) > mouseX;
    hoverY = m_y < mouseY && (m_y + m_h) > mouseY;

    return hoverX && hoverY;
}