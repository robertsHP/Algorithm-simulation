#include "Texture.h"
#include "SDL_rect.h"

Texture::Texture (char *fileLoc, SDL_Point templSize, SDL_Renderer *rend) {
    size_t       memSize;
    SDL_Point    realSize;
    bool         templApplies, templFits;
    SDL_Surface  *tempSurf;

    tempSurf = IMG_Load(fileLoc);

    if(!tempSurf) {
        printf("Texture : Failed to load surface from \"%s\"\n", fileLoc);
        return;
    }

    m_surface = SDL_ConvertSurfaceFormat(tempSurf, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_SetSurfaceBlendMode(m_surface, SDL_BLENDMODE_BLEND);

    if(m_surface) {
        templApplies = m_surface->w % templSize.x == 0 && m_surface->h % templSize.y == 0;
        templFits    = m_surface->w >= templSize.x && m_surface->h >= templSize.y;

        if(templApplies && templFits) {
            realSize.x = m_surface->w / templSize.x;
            realSize.y = m_surface->h / templSize.y;
            memSize = realSize.x * realSize.y;

            m_fileLoc = fileLoc;
            for(int row = 0; row < realSize.y; ++row) {
                for(int col = 0; col < realSize.x; ++col) {
                    m_tmplts[col + row * realSize.x] = (SDL_Rect) {
                        col * templSize.x,
                        row * templSize.y,
                        templSize.x,
                        templSize.y
                    };
                }
            }
            m_shSize = memSize;
            m_textr = SDL_CreateTextureFromSurface(rend, m_surface);
            if(!m_textr){
                printf("sprSh_Create : Failed to convert texture from surface. File -> \"%s\"\n", fileLoc);
            }
        } else printf("sprSh_Create : Failed to create from \"%s\"\n", fileLoc);
    }

    SDL_FreeSurface(tempSurf);
}
Texture::~Texture () {
    // Free(gpuSheet->tmplts, "sprSh_Create");
    if(m_surface) SDL_FreeSurface(m_surface);
    if(m_textr) SDL_DestroyTexture(m_textr);
}

void Texture::removeColor (SDL_Color color) {
    Uint32          rmColor;
    unsigned int    memSize;
    Uint32          *pixels;

    rmColor = color.r | (color.g << 8) | (color.b << 16) | (color.a << 24);

    SDL_LockSurface(m_surface);
    pixels = (Uint32*) m_surface->pixels;
    memSize = m_surface->w * m_surface->h;
    for(size_t i = 0; i < memSize; ++i)
        if(pixels[i] == rmColor)
            pixels[i] = 0x01;
    SDL_UnlockSurface(m_surface);

    SDL_Rect rect = {
        0, 0,
        m_surface->w,
        m_surface->h
    };

    SDL_UpdateTexture(
        m_textr,
        &rect,
        m_surface->pixels,
        m_surface->pitch
    );
}
