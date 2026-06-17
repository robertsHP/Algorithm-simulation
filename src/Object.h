#pragma once

#include "Scene.h"

class Object {
    protected:
        Scene *m_associatedScene;

        // std::unique_ptr<Texture> txtr;
        // unsigned txtrIndex;

        // union {
        //     struct { Uint8 r, g, b, a; };
        //     SDL_Color color;
        // };
        
        union {
            struct {
                int m_x, m_y;
                unsigned int m_w, m_h;
            };
            SDL_Rect m_rect;
        };

        // int          xVel, yVel;
        // double       angle;
        // SDL_Point    anglePoint;

        // //Position on the gameMap
        // union {
        //     struct { unsigned int xGM, yGM; };
        //     SDL_Point posGM;
        // };

    public:
        SDL_Rect& getRect () { return m_rect; }
        bool ifHoveredOver ();

    public:
        Object ();
        virtual ~Object ();

        virtual void input () {}
        virtual void update (float deltaTime) {}
        virtual void draw () {}
};