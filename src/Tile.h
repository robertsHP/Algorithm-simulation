#pragma once

#include <memory>

#include "Scene.h"
#include "Texture.h"
#include "Object.h"

class Tile : public Object {
    public:
        enum ID : unsigned {
            GREEN = 0,
            RED,
            
            COUNT
        };

        static const int TXTR_WIDTH = 30;
        static const int TXTR_HEIGHT = 16;

    private:
        Texture *m_txtr;
        ID m_id;

    public:
        void setID (ID id) { m_id = id; }   

    public:
        Tile (ID id, SDL_Point pos, Scene *scene);
        ~Tile () override;

        void input () override;
        void update (float deltaTime) override;
        void draw () override;
};

