#include "Objects.h"
#include "Engine.h"

void obj_SetTexture (Object *obj, size_t selTexture) {
    obj->txtrIndex = selTexture;
}
void obj_SetColor (Object *obj, SDL_Color *color) {
    obj->color = *color;
    SDL_SetTextureColorMod(
        obj->sheet->textr,
        color->r,
        color->g,
        color->b
    );
    SDL_SetTextureAlphaMod(obj->sheet->textr, color->a);
}
void obj_Move (Object *obj, int x, int y) {
    obj->x += x;
    obj->y += y;
}
void obj_SetPos (Object *obj, int x, int y) {
    obj->x = x;
    obj->y = y;
}
void obj_SetScale (Object *obj, unsigned int w, unsigned int h) {
    obj->w = w;
    obj->h = h;
}
void obj_Draw (Object *obj) {
    SDL_RenderCopyEx(
        g_win.rend,
        obj->sheet->textr,
        &obj->sheet->tmplts[obj->txtrIndex],
        &obj->rect,
        obj->angle,
        &obj->anglePoint,
        SDL_FLIP_NONE
    );
}
bool obj_HoveredOver (Object *obj, bool advanced) {
    bool hoverX, hoverY;
    SDL_Rect *curRect = &g_cursor.rect;

    hoverX = obj->x < curRect->x && (obj->x + obj->w) > curRect->x;
    hoverY = obj->y < curRect->y && (obj->y + obj->h) > curRect->y;

    if(hoverX && hoverY) {

    }

    return hoverX && hoverY;
}
