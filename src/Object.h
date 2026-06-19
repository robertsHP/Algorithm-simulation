#pragma once

#include "Scene.h"

class Object {
    protected:
        Scene *m_associatedScene;

        // std::unique_ptr<Texture> txtr;
        // unsigned txtrIndex;

        
        // union {
        //     struct { Uint8 m_r, m_g, m_b, m_a; };
        //     SDL_Color m_color;
        // };


        // unsigned int r = 255,g = 255,b = 255;
        // const float COLOR_UPDATE = 0.0166667;
            


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
        Object (SDL_Rect rect);
        virtual ~Object ();

        virtual void input () {}
        virtual void update (float deltaTime) {}
        virtual void draw () {}
};

