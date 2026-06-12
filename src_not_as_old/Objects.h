#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "DataTypes.h"

typedef struct {
    GPUSheet     *sheet;
    unsigned int txtrIndex;
    union {
        struct { Uint8 r, g, b, a; };
        SDL_Color color;
    };
    union {
        struct {
            int x, y;
            unsigned int w, h;
        };
        SDL_Rect rect;
    };
    int          xVel, yVel;
    double       angle;
    SDL_Point    anglePoint;
    //Position on the gameMap
    union {
        struct { unsigned int xGM, yGM; };
        SDL_Point posGM;
    };
} Object;

void obj_SetTexture (Object *obj, size_t selTexture);
void obj_SetColor (Object *obj, SDL_Color *color);
void obj_Move (Object *obj, int x, int y);
void obj_SetPos (Object *obj, int x, int y);
void obj_SetScale (Object *obj, unsigned int w, unsigned int h);
void obj_Draw (Object *obj);
