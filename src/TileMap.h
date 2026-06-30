#pragma once

#include <memory>

#include "Object.h"
#include "Tile.h"
#include "Enums.h"

class TileMap : public Object {
    private:
        std::map<int, std::unique_ptr<Tile>> m_isoTiles;
        std::map<int, std::unique_ptr<Tile>> m_topTiles;

        TileType m_viewType;

    public:
        std::unique_ptr<Tile>& getTile (SDL_Point pos) {
            return (m_viewType == TileType::ISOMETRIC) ?
                        m_isoTiles[pos.y * m_w + pos.x]
                        :
                        m_topTiles[pos.y * m_w + pos.x];
        }

    public:
        TileMap (SDL_Rect rect, TileType viewType, Scene *scene);

        void generateIsometricTileMap ();
        void generateTopTileMap ();

        ~TileMap () override;

        void input () override;
        void update (float deltaTime) override;
        void draw () override;
};

