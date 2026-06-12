#pragma once

#include "Objects.h"

typedef enum {
    BOARDTILE_TEX_LIGHT = 0,
    BOARDTILE_TEX_DARK,
    BOARDTILE_TEX_POS_MOV,
    BOARDTILE_TEX_IMPOS_MOV,
    BOARDTILE_TEX_SEL
} BoardTexture;

typedef struct {
    Object       obj;
    BoardTexture defTextr; //default texture
} BoardTile;

#define BOARDTILE_WIDTH 30
#define BOARDTILE_HEIGHT 16

void boardTile_LoadData (BoardTile *tile, SDL_Rect *rect, SDL_Point *posGM);
BoardTexture boardTile_GenTextureID ();
void boardTile_Update (BoardTile *tile);
bool boardTile_Input (BoardTile *tile, SDL_Event *event);
void boardTile_HeldInput (BoardTile *tile);
