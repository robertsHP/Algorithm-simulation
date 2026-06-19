#pragma once

#include "Scene.h"
#include "Texture.h"
#include "Object.h"

#include "Enums.h"

class StateButton : public Object {
    public:


        static const int TXTR_WIDTH = 24;
        static const int TXTR_HEIGHT = 24;

    private:
        Texture *m_txtr;
        SimState m_id;

    public:
        void setID (SimState id) { m_id = id; }

    public:
        StateButton (SimState id, SDL_Point pos, Scene *scene);
        ~StateButton () override;

        void input () override;
        void update (float deltaTime) override;
        void draw () override;

};

