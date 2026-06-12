#ifndef TEXTURE_H
#define TEXTURE_H

#include <memory>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"

#include "Debug.h"

// #include "ShaderProgram.h"

class Texture {
    private:
        char         *m_fileLoc;
        size_t        m_shSize;
        SDL_Texture  *m_textr;
        SDL_Surface  *m_surface;

        std::vector<SDL_Rect> m_tmplts;
    public:
        // Texture () = delete;
        Texture (char *fileLoc, SDL_Point templSize, SDL_Renderer *rend);
        ~Texture ();

        void removeColor(SDL_Color color);

    // public :
    //     // GLuint id;
    //     int width, height;
    //     std::string dir;

    //     // GLenum type;
    // public :
    //     Texture (std::string dir, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
    //     ~Texture ();

    //     void texUnit (std::shared_ptr<ShaderProgram> shader, const char* uniform, GLuint unit);
    //     void bind ();
    //     void unbind ();
};

#endif // TEXTURE_H
