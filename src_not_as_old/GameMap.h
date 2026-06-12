#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "BoardTile.h"
#include "Piece.h"

struct GameMap {
    BoardTile    *tiles;
    Piece        *wPieces;
    Piece        *bPieces;
    size_t       rowSize, colSize;
    unsigned int gapWidth, gapHeight;
} g_gMap;

#define MAP_SIZE 8

void gameMap_Init (unsigned int rowSize, unsigned int colSize);
void gameMap_GenerateBoardTile (SDL_Point *posGM, SDL_Rect *objPos, unsigned int objWidth, unsigned int objHeight);
void gameMap_Free ();
void gameMap_Input (SDL_Event *event);
void gameMap_Update ();
void gameMap_Draw ();
