#include "GameState.h"

void gameState_Init (State *state){
    state->stateTerm = &gameState_Free;
    state->input     = &gamestate_Input;
    state->update    = &gamestate_Update;
    state->draw      = &gamestate_Draw;

    g_gData.xVel = SCRN_X_MOV_VEL;
    g_gData.yVel = SCRN_Y_MOV_VEL;

    GPUSh_Create(&g_gData.sheets[GAME_SHEET_BOARD], "gfx/board.png", SDL_POINT(BOARDTILE_WIDTH, BOARDTILE_HEIGHT));
    GPUSh_RemoveColor(&g_gData.sheets[GAME_SHEET_BOARD], SDL_COLOR(255,0,255,255));
    gameMap_Init(MAP_SIZE, MAP_SIZE);

//    StrSmall test = "Hello nigger";
//    text_Create(&g_gData.nWord, test, &g_largeFont, SDL_RECT(200,300,FONT_LARGE_W,FONT_LARGE_H),40);
}
void gameState_Free () {
    gameMap_Free();
    GPUSh_Free(&g_gData.sheets[GAME_SHEET_BOARD]);
}
void gamestate_Input (SDL_Event *event) {
//    switch(event->type) {
//        case SDL_MOUSEBUTTONDOWN :
////            if(event->button.clicks == 1) {
////                printf("click once");
////            }
//        case SDL_MOUSEBUTTONUP : break;
//        case SDL_KEYDOWN :
//            if(event->key.repeat == 0) {
//                switch (event->key.keysym.scancode) {
//                    case SDL_SCANCODE_W : g_gData.yVel = -SCRN_Y_MOV_VEL; break;
//                    case SDL_SCANCODE_A : g_gData.xVel = -SCRN_X_MOV_VEL; break;
//                    case SDL_SCANCODE_S : g_gData.yVel = SCRN_Y_MOV_VEL; break;
//                    case SDL_SCANCODE_D : g_gData.xVel = SCRN_X_MOV_VEL; break;
//                    default : break;
//                }
//            }
//            break;
//        case SDL_KEYUP :
//            if(event->key.repeat == 0) {
//                switch (event->key.keysym.scancode) {
//                    case SDL_SCANCODE_D :
//                    case SDL_SCANCODE_A :
//                        g_gData.xVel = 0;
//                        break;
//                    case SDL_SCANCODE_W :
//                    case SDL_SCANCODE_S :
//                        g_gData.yVel = 0;
//                        break;
//                    default : break;
//                }
//            }
//        default : break;
//    }
    gameMap_Input(event);
}
void gamestate_InputHeld () {
//    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
//
//    if(keyState[SDL_SCANCODE_LSHIFT] || keyState[SDL_SCANCODE_RSHIFT]) {
//        if(g_gData.xVel != SCRN_X_MOV_VEL_FAST || g_gData.yVel != SCRN_Y_MOV_VEL_FAST) {
//            g_gData.xVel = SCRN_X_MOV_VEL_FAST;
//            g_gData.yVel = SCRN_Y_MOV_VEL_FAST;
//        }
//    } else {
//        if(g_gData.xVel != SCRN_X_MOV_VEL || g_gData.yVel != SCRN_Y_MOV_VEL) {
//            g_gData.xVel = SCRN_X_MOV_VEL;
//            g_gData.yVel = SCRN_Y_MOV_VEL;
//        }
//    }
}
void gamestate_Update () {
    gamestate_InputHeld();
    gameMap_Update();
}
void gamestate_Draw () {
    gameMap_Draw();
//    text_Draw(&g_gData.nWord);
}
