#pragma once

#include "Scene.h"
#include "Texture.h"
#include "Object.h"

class StateButton : public Object {
    public:
        enum ID : unsigned {
            START = 0,
            END,
            RESET,
            
            COUNT
        };

        static const int TXTR_WIDTH = 24;
        static const int TXTR_HEIGHT = 24;

    private:
        Texture *m_txtr;
        ID m_id;

    public:
        void setID (ID id) { m_id = id; }

    public:
        StateButton (ID id, SDL_Point pos, Scene *scene);
        ~StateButton () override;

        void input () override;
        void update (float deltaTime) override;
        void draw () override;

    private:
        void startAction ();
        void endAction ();
        void resetAction ();

};

