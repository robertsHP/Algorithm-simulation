#include "BoardTile.h"
#include "GameState.h"

void boardTile_LoadData (BoardTile *tile, SDL_Rect *rect, SDL_Point *posGM) {
    tile->obj.posGM = *posGM;
    tile->obj.rect = *rect;
    tile->obj.angle = 0;
    tile->obj.anglePoint.x = rect->x + rect->w / 2;
    tile->obj.anglePoint.y = rect->y + rect->h / 2;

    tile->obj.sheet = &g_gData.sheets[GAME_SHEET_BOARD];
    tile->obj.txtrIndex = boardTile_GenTextureID();
    obj_SetColor(&tile->obj, &SDL_COLOR(255, 255, 255, 255));
}
BoardTexture boardTile_GenTextureID () {
    static bool offset = false;
    static unsigned int textrCounter = 0;
    BoardTexture id;

    if(textrCounter % 2 == 0)
        id = BOARDTILE_TEX_LIGHT;
    else id = BOARDTILE_TEX_DARK;
    textrCounter++;
    if(textrCounter % (MAP_SIZE + offset) == 0) {
        offset = !offset;
        textrCounter = offset;
    }
    return id;
}
void boardTile_Update (BoardTile *tile) {
    boardTile_HeldInput(tile);
}
bool boardTile_Input (BoardTile *tile, SDL_Event* event) {
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
void boardTile_HeldInput (BoardTile *tile) {
//    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
//
//    if(keyState[SDL_SCANCODE_W]) oData->y += g_gData.yVel;
//    if(keyState[SDL_SCANCODE_A]) oData->x += g_gData.xVel;
//    if(keyState[SDL_SCANCODE_S]) oData->y -= g_gData.yVel;
//    if(keyState[SDL_SCANCODE_D]) oData->x -= g_gData.xVel;
}
