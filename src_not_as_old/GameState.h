#pragma once

#include "Engine.h"
#include "GameMap.h"

#define SCRN_X_MOV_VEL 4
#define SCRN_Y_MOV_VEL 4
#define SCRN_X_MOV_VEL_FAST 7
#define SCRN_Y_MOV_VEL_FAST 7

enum GameSheetIDs {
    GAME_SHEET_BOARD = 0,
    GAME_SHEET_PIECES,
    GAME_SHEET_MAX
};

struct GameStateData {
    GPUSheet    sheets [GAME_SHEET_MAX];
    int         xVel, yVel;
    Text        nWord;
} g_gData;

void gameState_Init (State *state);
void gameState_Free ();
void gamestate_Input (SDL_Event *event);
void gamestate_InputHeld ();
void gamestate_Update ();
void gamestate_Draw ();


