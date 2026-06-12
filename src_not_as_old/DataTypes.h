#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "SDL.h"
#include "SDL_image.h"

/////////////////////////////////////////////////////////////////////////////////////////////
/*
    Custom memory management functions

    Functions :
    -MAlloc - works pretty much the same as malloc() except it prints the allocated memory size
    and a memory name to the console.
    -Free - same as free() except for MAlloc.
*/
/////////////////////////////////////////////////////////////////////////////////////////////

    struct MemAllocInfo {
        size_t allocCount;
        size_t freeCount;
    } g_allocInfo;

    void* MAlloc (size_t allocSize, char *locInCode);
    void Free (void *ptr, char *locInCode);

/////////////////////////////////////////////////////////////////////////////////////////////
/*
    GPU Sheets

    -GPUSheet - before usage they need to be created using the GPUSh_Create function which will allocate
    area on the heap based on imgSize and templSize. After done using its mandatory to use the GPUSh_Free
    function to free memory.
*/
/////////////////////////////////////////////////////////////////////////////////////////////

    typedef struct {
        char         *fileLoc;
        SDL_Rect     *tmplts;
        size_t       shSize;
        SDL_Texture  *textr;
        SDL_Surface  *surface;
    } GPUSheet;

    void GPUSh_Create (GPUSheet *sprSheet, char *fileLoc, SDL_Point templSize);
    void GPUSh_RemoveColor (GPUSheet *sprSheet, SDL_Color color);
    void GPUSh_Free (GPUSheet *sprSheet);

////////////////////////////////////////////////////////////////////////////
/*
    Fonts and text
*/
////////////////////////////////////////////////////////////////////////////

    #define FONT_LARGE_W 11
    #define FONT_LARGE_H 13

    GPUSheet g_largeFont;

    void fonts_Load ();
    void fonts_Free ();

    #define STR_SMALL_SIZE 255
    typedef char StrSmall [STR_SMALL_SIZE];

    typedef struct {
        char         txtBuffer[STR_SMALL_SIZE];
        SDL_Rect     chars[STR_SMALL_SIZE];
        size_t       finStrSize;
        unsigned int lineLim;
        GPUSheet     *font;
        union {
            struct {
                int x, y;
                unsigned int w, h;
            };
            SDL_Rect pos;
        };
        int charGap, lineGap;
    } Text;

    void text_Create (Text *text, StrSmall txt, GPUSheet *font, SDL_Rect pos, unsigned int newLineLim);
    void text_LoadCharacters (Text *text);
    void text_Draw (Text *text);

/////////////////////////////////////////////////////////////////////////////////////////////
/*
    ADDITIONS FOR SDL
*/
/////////////////////////////////////////////////////////////////////////////////////////////

    #define SDL_RECT(x,y,w,h) (SDL_Rect) {x,y,w,h}   ///Direct way of passing an SDL_Rect structure
    #define SDL_POINT(x,y) (SDL_Point) {x,y}         ///Direct way of passing an SDL_Point structure
    #define SDL_COLOR(r,g,b,a) (SDL_Color) {r,g,b,a} ///Direct way of passing an SDL_Color structure
