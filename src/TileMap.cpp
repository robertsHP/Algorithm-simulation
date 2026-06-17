#include "TileMap.h"


TileMap::TileMap (SDL_Point pos, SDL_Point size, Scene *scene) {
    m_associatedScene = scene;

    int offsetRow, offsetCol;

    offsetRow = offsetCol = 0;
    
    m_gapWidth = Tile::TXTR_WIDTH * 2;
    m_gapHeight = Tile::TXTR_HEIGHT * 2;
    
    m_rect = { pos.x, pos.y, size.x, size.y };

    for(int row = 0; row < m_rect.h; ++row) {
        offsetRow = 0;

        for(int col = 0; col < m_rect.w; ++col) {
            int finalColVal = col * m_gapWidth / 2 + offsetCol;
            int finalRowVal = row * m_gapHeight / 2 + offsetRow;

            finalColVal += pos.x;
            finalRowVal += pos.y;

            m_tiles.insert_or_assign(
                row * m_rect.w + col, 
                std::make_unique<Tile>(
                    Tile::ID::RED, 
                    (SDL_Point) {finalColVal, finalRowVal}, 
                    scene
                )
            );

            offsetRow += m_gapHeight / 2;
        }
        offsetCol -= m_gapWidth / 2;
    }
}

TileMap::~TileMap () {
    Debug::log("INFO", "Destroy TileMap.");
}

void TileMap::input () {

}

void TileMap::update (float deltaTime) {
    // for (const auto& [pos, tile] : m_tiles) {
    //     if(tile)
    //         tile->draw();
    // }
}

void TileMap::draw () {
    for (const auto& [pos, tile] : m_tiles) {
        if(tile)
            tile->draw();
    }
}