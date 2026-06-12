#include "Piece.h"
#include "GameState.h"

void piece_LoadData (Piece *piece) {
    piece->obj.sheet = &g_gData.sheets[GAME_SHEET_PIECES];
    piece->obj.txtrIndex = 0;
    obj_SetColor(&piece->obj, &SDL_COLOR(255, 255, 255, 255));
}
void piece_Update (Piece *piece) {
    piece_HeldInput(piece);
}
bool piece_Input (Piece *piece, SDL_Event* event) {
//    switch(event->type) {
//        case SDL_MOUSEBUTTONDOWN :
////            if(event->button.clicks == 1) {
////                printf("click once");
////            }
//        case SDL_MOUSEBUTTONUP : break;
//        case SDL_KEYDOWN :
////            if(event->key.repeat == 0) {
////                printf("press once");
////            }
//            switch (event->key.keysym.scancode) {
//                default : break;
//            }
//        case SDL_KEYUP :
//            switch (event->key.keysym.scancode) {
//                default : break;
//            }
//        default : break;
//    }
    return false;
}
void piece_HeldInput (Piece *piece) {
//    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
//
//    if(keyState[SDL_SCANCODE_W]) oData->y += g_gData.yVel;
//    if(keyState[SDL_SCANCODE_A]) oData->x += g_gData.xVel;
//    if(keyState[SDL_SCANCODE_S]) oData->y -= g_gData.yVel;
//    if(keyState[SDL_SCANCODE_D]) oData->x -= g_gData.xVel;
}
