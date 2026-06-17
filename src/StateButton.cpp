#include "StateButton.h"

#include "Input.h"
#include "SDL_events.h"

#include "main.h"

StateButton::StateButton (ID id, SDL_Point pos, Scene *scene) {
    m_associatedScene = scene;

    m_txtr = m_associatedScene->getTexture("state_btns");

    m_id = id;
    m_rect = (SDL_Rect) { pos.x, pos.y, TXTR_WIDTH * 2, TXTR_HEIGHT * 2 };
}
StateButton::~StateButton () {
    Debug::log("INFO", "Destroying StateButton.");
}

void StateButton::input () {
    if(ifHoveredOver()) {
        if(Input::mouseReleased(SDL_BUTTON_LEFT)) {
            switch (m_id) {
                case START:
                    startAction();
                    break;
                case END:
                    endAction();
                    break;
                case RESET:
                    resetAction();
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

void StateButton::startAction () {
    printf("startAction\n");
}
void StateButton::endAction () {
    printf("endAction\n");
}
void StateButton::resetAction () {
    printf("resetAction\n");
}
