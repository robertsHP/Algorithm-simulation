#include "GameMap.h"
#include "BoardTile.h"
#include "Engine.h"

void gameMap_Init (unsigned int rowSize, unsigned int colSize) {
    int          offsetRow, offsetCol;
    SDL_Rect     objPos;

    offsetRow = 0;
    offsetCol = 0;
    g_gMap.gapWidth = BOARDTILE_WIDTH * 2;
    g_gMap.gapHeight = BOARDTILE_HEIGHT * 2;
    g_gMap.rowSize = rowSize;
    g_gMap.colSize = colSize;
    g_gMap.tiles = MAlloc(sizeof(BoardTile) * (rowSize * colSize), "Tile map");

    for(size_t row = 0; row < rowSize; ++row) {
        offsetRow = 0;
        for(size_t col = 0; col < colSize; ++col) {
            objPos = SDL_RECT(
                col * g_gMap.gapWidth / 2 + offsetCol,
                row * g_gMap.gapHeight / 2 + offsetRow,
                g_gMap.gapWidth,
                g_gMap.gapHeight
            );
            gameMap_GenerateBoardTile(
                &SDL_POINT(col, row),
                &objPos,
                g_gMap.gapWidth,
                g_gMap.gapHeight
            );
            offsetRow += g_gMap.gapHeight / 2;
        }
        offsetCol -= g_gMap.gapWidth / 2;
    }
}
void gameMap_GenerateBoardTile (SDL_Point *posGM, SDL_Rect *objPos, unsigned int gapWidth, unsigned int gapHeight) {
    const size_t index = posGM->x + posGM->y * g_gMap.colSize;
    boardTile_LoadData(
        &g_gMap.tiles[index],
        objPos,
        posGM
    );
    obj_Move(
        &g_gMap.tiles[index].obj,
        g_win.w / 2 - gapWidth / 2,
        g_win.h / 2 - (g_gMap.rowSize * gapHeight) / 2
    );
}
void gameMap_Free () {
    Free(&g_gMap.tiles, "Tile map");
}
void gameMap_Input (SDL_Event *event) {
    size_t rowSize, colSize;
    BoardTile *tile;

    rowSize = g_gMap.rowSize;
    colSize = g_gMap.colSize;

    for(size_t row = 0; row < rowSize; ++row) {
        for(size_t col = 0; col < colSize; ++col) {
            tile = &g_gMap.tiles[col + row * colSize];
            boardTile_Input(tile, event);
        }
    }
}
void gameMap_Update () {
    size_t rowSize, colSize;
    BoardTile *tile;

    rowSize = g_gMap.rowSize;
    colSize = g_gMap.colSize;

    for(size_t row = 0; row < rowSize; ++row) {
        for(size_t col = 0; col < colSize; ++col) {
            tile = &g_gMap.tiles[col + row * colSize];
            boardTile_Update(tile);
        }
    }
}
void gameMap_Draw () {
    unsigned int  rowSize, colSize;
    bool          inBoundsX, inBoundsY;
    BoardTile     *tile;

    rowSize = g_gMap.rowSize;
    colSize = g_gMap.colSize;

    for(size_t row = 0; row < rowSize; ++row) {
        for(size_t col = 0; col < colSize; ++col) {
            tile = &g_gMap.tiles[col + row * colSize];

            inBoundsX = tile->obj.x > 0 && tile->obj.x + tile->obj.w < g_win.w;
            inBoundsY = tile->obj.y > 0 && tile->obj.y + tile->obj.h < g_win.h;
            if(inBoundsX && inBoundsY)
                obj_Draw(&tile->obj);
        }
    }
}
