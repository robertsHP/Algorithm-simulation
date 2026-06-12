#include "DataTypes.h"
#include "Engine.h"

void* MAlloc (size_t allocSize, char *locInCode) {
    printf("%d = !!!Allocating %d bytes with label \"%s\"\n", g_allocInfo.allocCount, allocSize, locInCode);
    g_allocInfo.allocCount++;
    return malloc(allocSize);
}
void Free (void *ptr, char *locInCode) {
    if(ptr) {
        printf("%d = !!!Freeing with label \"%s\"\n", g_allocInfo.freeCount, locInCode);
        free(ptr);
        g_allocInfo.freeCount++;
    } else printf("%d = !!!Memory doesn't exist. Skipped \"%s\".\n",  g_allocInfo.freeCount, locInCode);
}

void GPUSh_Create (GPUSheet *gpuSheet, char *fileLoc, SDL_Point templSize) {
    size_t       memSize;
    SDL_Point    realSize;
    bool         templApplies, templFits;
    SDL_Surface  *tempSurf;

    tempSurf = IMG_Load(fileLoc);
    if(tempSurf) {
        gpuSheet->surface = SDL_ConvertSurfaceFormat(tempSurf, SDL_PIXELFORMAT_ARGB8888, 0);
        SDL_SetSurfaceBlendMode(gpuSheet->surface, SDL_BLENDMODE_BLEND);
        if(gpuSheet->surface) {
            templApplies = gpuSheet->surface->w % templSize.x == 0 && gpuSheet->surface->h % templSize.y == 0;
            templFits    = gpuSheet->surface->w >= templSize.x && gpuSheet->surface->h >= templSize.y;
            if(templApplies && templFits) {
                realSize.x = gpuSheet->surface->w / templSize.x;
                realSize.y = gpuSheet->surface->h / templSize.y;
                memSize = realSize.x * realSize.y;
                gpuSheet->tmplts = MAlloc(sizeof(SDL_Rect) * memSize, "sprSh_Create");
                if(gpuSheet->tmplts != NULL) {
                    gpuSheet->fileLoc = fileLoc;
                    for(size_t row = 0; row < realSize.y; ++row) {
                        for(size_t col = 0; col < realSize.x; ++col) {
                            gpuSheet->tmplts[col + row * realSize.x] = (SDL_Rect) {
                                col * templSize.x,
                                row * templSize.y,
                                templSize.x,
                                templSize.y
                            };
                        }
                    }
                    gpuSheet->shSize = memSize;
                    gpuSheet->textr = SDL_CreateTextureFromSurface(g_win.rend, gpuSheet->surface);
                    if(!gpuSheet->textr){
                        printf("sprSh_Create : Failed to convert texture from surface. File -> \"%s\"\n", fileLoc);
                    }
                } else printf("sprSh_Create : Failed to allocate memory for Sprite Sheet templates. File -> \"%s\"\n", fileLoc);
            } else printf("sprSh_Create : Failed to create from \"%s\"\n", fileLoc);
        } else printf("sprSh_Create : Failed to convert surface from \"%s\"\n", fileLoc);
        SDL_FreeSurface(tempSurf);
    } else printf("sprSh_Create : Failed to load surface from \"%s\"\n", fileLoc);
}
void GPUSh_RemoveColor (GPUSheet *gpuSheet, SDL_Color color) {
    Uint32          rmColor;
    unsigned int    memSize;
    Uint32          *pixels;

    rmColor = color.r | (color.g << 8) | (color.b << 16) | (color.a << 24);

    SDL_LockSurface(gpuSheet->surface);
    pixels = (Uint32*) gpuSheet->surface->pixels;
    memSize = gpuSheet->surface->w * gpuSheet->surface->h;
    for(size_t i = 0; i < memSize; ++i)
        if(pixels[i] == rmColor)
            pixels[i] = 0x01;
    SDL_UnlockSurface(gpuSheet->surface);
    SDL_UpdateTexture(
        gpuSheet->textr,
        &SDL_RECT(
            0, 0,
            gpuSheet->surface->w,
            gpuSheet->surface->h
        ),
        gpuSheet->surface->pixels,
        gpuSheet->surface->pitch
    );
}
void GPUSh_Free (GPUSheet *gpuSheet) {
    Free(gpuSheet->tmplts, "sprSh_Create");
    if(gpuSheet->surface) SDL_FreeSurface(gpuSheet->surface);
    if(gpuSheet->textr) SDL_DestroyTexture(gpuSheet->textr);
}

void fonts_Load () {
    GPUSh_Create(&g_largeFont, "gfx/font.png", SDL_POINT(11,13));
    GPUSh_RemoveColor(&g_largeFont, SDL_COLOR(255,0,255,255));
}
void fonts_Free () {
    GPUSh_Free(&g_largeFont);
}
void text_Create (Text *text, StrSmall txt, GPUSheet *font, SDL_Rect pos, unsigned int lineLim) {
    strcpy(text->txtBuffer, txt);
    text->font = font;
    text->pos = pos;
    text->charGap = pos.w / FONT_LARGE_W;
    text->lineGap = pos.h / FONT_LARGE_H;
    text->lineLim = lineLim;
    text_LoadCharacters(text);
}
void text_LoadCharacters (Text *text) {
    unsigned int curChar;

    text->finStrSize = 0;
    for(size_t i = 0; i < STR_SMALL_SIZE; ++i) {
        curChar = text->txtBuffer[i];
        if(curChar == '\0')
            break;
        text->chars[i] = text->font->tmplts[curChar - 32];
        text->finStrSize++;
    }
}
void text_Draw (Text *text) {
    int     posX, posY;
    size_t  chIndex;

    posY = text->y;
    for(size_t row = 0; row < STR_SMALL_SIZE; ++row) {
        posX = text->x;
        for(size_t col = 0; col < text->lineLim; ++col){
            chIndex = col + row * text->lineLim;
            if(chIndex > text->finStrSize){
                return;
            } else if (text->txtBuffer[chIndex] == '\n') {
                posX = text->x;
                posY += FONT_LARGE_H + text->lineGap;
                continue;
            }
            SDL_RenderCopyEx(
                g_win.rend,
                text->font->textr,
                &text->chars[chIndex],
                &SDL_RECT(
                    posX * text->charGap,
                    posY * text->lineGap,
                    text->w, text->h),
                0,
                NULL,
                SDL_FLIP_NONE
            );
            posX += FONT_LARGE_W + text->charGap;
        }
        posY += FONT_LARGE_H + text->lineGap;
    }
}
