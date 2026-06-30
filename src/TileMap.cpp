#include "TileMap.h"
#include "Enums.h"

TileMap::TileMap (
    SDL_Rect rect, TileType startingTileType, Scene *scene
) : Object(rect) 
{
    m_viewType = startingTileType;
    m_associatedScene = scene;

    generateIsometricTileMap();
    generateTopTileMap();
}

void TileMap::generateIsometricTileMap () {
    int offsetRow, offsetCol;

    offsetRow = offsetCol = 0;
    
    int gapWidth = Tile::TXTR_WIDTH * 2;
    int gapHeight = Tile::TXTR_HEIGHT;

    for(int row = 0; row < m_rect.h; ++row) {
        offsetRow = 0;

        for(int col = 0; col < m_rect.w; ++col) {
            int finalColVal = col * gapWidth / 2 + offsetCol;
            int finalRowVal = row * gapHeight / 2 + offsetRow;

            finalColVal += m_rect.x;
            finalRowVal += m_rect.y;

            m_isoTiles.insert_or_assign(
                row * m_rect.w + col, 
                std::make_unique<Tile>(
                    Tile::ID::RED, 
                    (SDL_Point) {finalColVal, finalRowVal},
                    TileType::ISOMETRIC,
                    m_associatedScene
                )
            );

            offsetRow += gapHeight / 2;
        }
        offsetCol -= gapWidth / 2;
    }
}

void TileMap::generateTopTileMap () {
    int offsetRow, offsetCol;

    offsetRow = offsetCol = 0;

    int gapWidth = Tile::TXTR_WIDTH;
    int gapHeight = Tile::TXTR_HEIGHT;
    
    for(int row = 0; row < m_rect.h; ++row) {
        offsetRow = 0;

        for(int col = 0; col < m_rect.w; ++col) {
            int finalColVal = col * gapWidth;
            int finalRowVal = row * gapHeight;

            finalColVal += m_rect.x;
            finalRowVal += m_rect.y;

            m_topTiles.insert_or_assign(
                row * m_rect.w + col, 
                std::make_unique<Tile>(
                    Tile::ID::RED, 
                    (SDL_Point) {finalColVal, finalRowVal},
                    TileType::ISOMETRIC,
                    m_associatedScene
                )
            );

            offsetCol += m_rect.w;
        }
        
        offsetRow += m_rect.h;
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
    auto &tiles = (m_viewType == TileType::ISOMETRIC) ?
                    m_isoTiles : m_topTiles;

    for (const auto& [pos, tile] : tiles) {
        if(tile)
            tile->draw();
    }
}