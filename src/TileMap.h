#pragma once

#include <memory>

#include "Object.h"
#include "Tile.h"

class TileMap : public Object {
    public:
        enum View {
            ISOMETRIC, TOP
        };

    private:
        std::map<int, std::unique_ptr<Tile>> m_tiles;

        // Piece *wPieces;
        // Piece *bPieces;

        int m_gapWidth, m_gapHeight;

    public:
        std::unique_ptr<Tile>& getTile (SDL_Point pos) { 
            return m_tiles[pos.y * m_w + pos.x]; 
        }

    public:
        TileMap (SDL_Point pos, SDL_Point size, Scene *scene);
        ~TileMap () override;

        void input () override;
        void update (float deltaTime) override;
        void draw () override;
};

