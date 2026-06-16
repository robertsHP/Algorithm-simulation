#include "Texture.h"

#include "Engine.h"
#include "SDL_rect.h"

Texture::Texture (std::string fileLoc, SDL_Renderer *rend) {
    reload(fileLoc, rend);
}

Texture::~Texture () {
    Debug::log("INFO", "Destroying texture " + m_fileLoc + ".");

    // Free(gpuSheet->tmplts, "sprSh_Create");

    if(m_surface) SDL_FreeSurface(m_surface);
    if(m_textr) SDL_DestroyTexture(m_textr);
}

void Texture::reload (std::string fileLoc, SDL_Renderer *rend) {
    Debug::log("INFO", "Loading texture " + fileLoc + ".");

    SDL_Surface *img_surf;

    m_fileLoc = fileLoc;

    m_rendPtr = rend;
    img_surf = IMG_Load(m_fileLoc.c_str());

    if(!img_surf) {
        printf("Texture : Failed to load surface from \"%s\"\n", m_fileLoc.c_str());
        return;
    }

    m_surface = SDL_ConvertSurfaceFormat(img_surf, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_SetSurfaceBlendMode(m_surface, SDL_BLENDMODE_BLEND);

    if(m_surface) {
        m_textr = SDL_CreateTextureFromSurface(rend, m_surface);

        if(!m_textr){
            printf("Texture : Failed to convert texture from surface. File -> \"%s\"\n", m_fileLoc.c_str());
        }

        m_tmplts.push_back({ 0, 0, m_surface->w, m_surface->h });
    }

    SDL_FreeSurface(img_surf);
}

void Texture::generateSheetTemplates (SDL_Point templSize) {
    size_t       memSize;
    SDL_Point    realSize;
    bool         templApplies, templFits;

    m_tmplts.clear();

    if(m_surface) {
        templApplies = m_surface->w % templSize.x == 0 && m_surface->h % templSize.y == 0;
        templFits    = m_surface->w >= templSize.x && m_surface->h >= templSize.y;

        if(templApplies || templFits) {
            realSize.x = m_surface->w / templSize.x;
            realSize.y = m_surface->h / templSize.y;
            memSize = realSize.x * realSize.y;

            for(int row = 0; row < realSize.y; ++row) {
                for(int col = 0; col < realSize.x; ++col) {
                    // unsigned id = col + row * realSize.x;

                    m_tmplts.push_back(
                        (SDL_Rect) {
                            col * templSize.x,
                            row * templSize.y,
                            templSize.x,
                            templSize.y
                        }
                    );
                }
            }
        } 
        // else printf("TextureSheet : Failed to create from \"%s\"\n", fileLoc);
    }

    printf("m_tmplts count = %d\n", (int) m_tmplts.size());
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

void Texture::draw (
    unsigned templID,
    SDL_Rect *drawShape,
    double angle,
    SDL_Point *anglePoint,
    SDL_RendererFlip flip
) {
    static Engine &engine = Engine::getInstance();

    SDL_RenderCopyEx(
        engine.getWindowData().rendPtr,
        m_textr,
        &m_tmplts[templID],
        drawShape,
        angle,
        anglePoint,
        flip
    );
}

void Texture::draw (
    SDL_Rect *drawShape,
    double angle,
    SDL_Point *anglePoint,
    SDL_RendererFlip flip
) {
    static Engine &engine = Engine::getInstance();

    SDL_Rect srcRect = { 0, 0, m_surface->w, m_surface->h };

    SDL_RenderCopyEx(
        engine.getWindowData().rendPtr,
        m_textr,
        &srcRect,
        drawShape,
        angle,
        anglePoint,
        flip
    );
}


// TextureSheet::TextureSheet (
//     std::string fileLoc, 
//     SDL_Point templSize, 
//     SDL_Renderer *rend
// ) : Texture(fileLoc, rend) {
//     size_t       memSize;
//     SDL_Point    realSize;
//     bool         templApplies, templFits;

//     if(m_surface) {
//         templApplies = m_surface->w % templSize.x == 0 && m_surface->h % templSize.y == 0;
//         templFits    = m_surface->w >= templSize.x && m_surface->h >= templSize.y;

//         if(templApplies && templFits) {
//             realSize.x = m_surface->w / templSize.x;
//             realSize.y = m_surface->h / templSize.y;
//             memSize = realSize.x * realSize.y;

//             for(int row = 0; row < realSize.y; ++row) {
//                 for(int col = 0; col < realSize.x; ++col) {
//                     m_tmplts[col + row * realSize.x] = (SDL_Rect) {
//                         col * templSize.x,
//                         row * templSize.y,
//                         templSize.x,
//                         templSize.y
//                     };
//                 }
//             }
//             m_shSize = memSize;
//         } 
//         // else printf("TextureSheet : Failed to create from \"%s\"\n", fileLoc);
//     }
// }

// void TextureSheet::draw () {
//     static Engine &engine = Engine::getInstance();

//     SDL_RenderCopyEx(
//         engine.getWindowData().rendPtr,
//         m_textr,
//         &obj->sheet->tmplts[obj->txtrIndex],
//         &obj->rect,
//         obj->angle,
//         &obj->anglePoint,
//         SDL_FLIP_NONE
//     );
// }



