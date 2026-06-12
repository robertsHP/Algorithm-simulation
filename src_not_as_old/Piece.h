#pragma once

#include "Objects.h"

typedef enum {
    PIECE_TEX_PAWN = 0,
    PIECE_TEX_KNIGHT,
    PIECE_TEX_ROOK,
    PIECE_TEX_BISHOP,
    PIECE_TEX_QUEEN,
    PIECE_TEX_KING,
        PIECE_TEX_MAX
} PieceTexture;

typedef struct {
    Object       obj;
    PieceTexture defTextr; //default texture
} Piece;

#define PIECE_WHITE_START 0
#define PIECE_BLACK_START 6

#define PIECE_WIDTH 15
#define PIECE_HEIGHT 27

void piece_LoadData (Piece *obj);
void piece_Update (Piece *obj);
bool piece_Input (Piece *obj, SDL_Event *event);
void piece_HeldInput (Piece *obj);

