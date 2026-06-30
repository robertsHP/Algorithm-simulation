#include "PerlinNoise.h"


PerlinNoise::PerlinNoise (TileMap *tileMap) {
    m_tileMap = tileMap;

    Debug::log("INFO", "Init CellularAutomata.");

    init();
}

PerlinNoise::~PerlinNoise () {
    Debug::log("INFO", "Destroy CellularAutomata.");
    free();
}

void PerlinNoise::init () {
    // SDL_Rect &tileMapRect = m_tileMap->getRect();

    // size_t mapSize = tileMapRect.w * tileMapRect.h;

    // m_output = new int [mapSize];
    // m_state = new int [mapSize];
    // memset(m_output, 0, mapSize * sizeof(int));
    // memset(m_state, 0, mapSize * sizeof(int));

    // for (int i = 0; i < mapSize; i++)
    //     m_state[i] = rand() % 2;

    // auto set = [&](int x, int y, std::wstring s)
    // {
    //     int p = 0;
    //     for (auto c : s)
    //     {
    //         m_state[y * tileMapRect.w + x + p] = c == L'#' ? 1 : 0;
    //         p++;
    //     }
    // };

    // m_timer.start();
}

void PerlinNoise::free () {
    // if (m_output) delete m_output;
    // if (m_state) delete m_state;
}

void PerlinNoise::reset() {
    Debug::log("INFO", "Reset CellularAutomata.");

    free ();
    init ();
}

void PerlinNoise::updateTiles () {
    // if (!m_timer.ifTimePassed(80))
    //     return;

    // SDL_Rect &tileMapRect = m_tileMap->getRect();

    // auto cell = [&](int x, int y)
    // {
    //     return m_output[y * tileMapRect.w + x];
    // };

    // // Store output state
    // for (int i = 0; i < tileMapRect.w * tileMapRect.h; i++)
    //     m_output[i] = m_state[i];
    
    // for (int x = 0; x < tileMapRect.w; x++) {
    //     for (int y = 0; y < tileMapRect.h; y++)
    //     {
    //         int nNeighbours =	cell(x - 1, y - 1) + cell(x - 0, y - 1) + cell(x + 1, y - 1) +
    //                             cell(x - 1, y + 0) +          0         + cell(x + 1, y + 0) +
    //                             cell(x - 1, y +	1) + cell(x + 0, y + 1) + cell(x + 1, y + 1);

    //         if (cell(x, y) == 1)
    //             m_state[y * tileMapRect.w + x] = nNeighbours == 2 || nNeighbours == 3;
    //         else
    //             m_state[y * tileMapRect.w + x] = nNeighbours == 3;

    //         std::unique_ptr<Tile>& tile = m_tileMap->getTile({x, y});

    //         if(tile) {
    //             // printf("x = %d; y = %d\n", x, y);

    //             if (cell(x, y) == 1)
    //                 // ncurses->drawChar(x, y, '1', NCurses::Colors::FG_WHITE_BG_BLACK);
    //                 tile->setID(Tile::GREEN);
    //             else
    //                 tile->setID(Tile::RED);
    //                 // ncurses->drawChar(x, y, '0', NCurses::Colors::FG_BLUE_BG_BLACK);
    //         }
    //     }
    // }
}