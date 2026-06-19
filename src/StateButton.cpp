#include "StateButton.h"

#include "Input.h"
#include "MainScene.h"

#include "SDL_events.h"

#include "main.h"

StateButton::StateButton (SimState id, SDL_Point pos, Scene *scene) 
: Object(
    { pos.x, pos.y, TXTR_WIDTH * 2, TXTR_HEIGHT * 2 }
) {
    m_associatedScene = scene;

    m_txtr = m_associatedScene->getTexture("state_btns");

    m_id = id;
}
StateButton::~StateButton () {
    Debug::log("INFO", "Destroying StateButton.");
}

void StateButton::input () {
    if(ifHoveredOver()) {
        if(Input::mouseReleased(SDL_BUTTON_LEFT)) {
            switch (m_id) {
                case SimState::START:
                    ((MainScene*) m_associatedScene)->setCurrentSimState(SimState::START);
                    break;
                case SimState::STOP:
                    ((MainScene*) m_associatedScene)->setCurrentSimState(SimState::STOP);
                    break;
                case SimState::RESET:
                    ((MainScene*) m_associatedScene)->setCurrentSimState(SimState::RESET);
                    break;
            }
        }
    }
}
void StateButton::update (float deltaTime) {

}
void StateButton::draw () {
    m_txtr->draw(m_id, &m_rect, 0, NULL, SDL_FLIP_NONE);
}
