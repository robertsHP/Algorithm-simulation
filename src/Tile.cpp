#include "Tile.h"

#include "Engine.h"

Tile::Tile (ID id, SDL_Point pos, Scene *scene) 
: Object(
    {pos.x, pos.y, TXTR_WIDTH * 2, TXTR_HEIGHT * 2}
    // {255, 255, 255, 255}
)
{
    m_associatedScene = scene;

    m_txtr = m_associatedScene->getTexture("board");

    m_id = id;
}
Tile::~Tile () {
    // Debug::log("INFO", "Destroying Tile.");
}

void Tile::input () {

}

void Tile::update (float deltaTime) {

}

void Tile::draw () {

    
    m_txtr->draw(m_id, &m_rect, 0, NULL, SDL_FLIP_NONE);
    

    // &obj->sheet->tmplts[obj->txtrIndex]

    // SDL_RenderCopyEx(
    //     g_win.rend,
    //     obj->sheet->textr,
    //     &obj->sheet->tmplts[obj->txtrIndex],
    //     &obj->rect,
    //     obj->angle,
    //     &obj->anglePoint,
    //     SDL_FLIP_NONE
    // );
}

