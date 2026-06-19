#include "CellularAutomata.h"

CellularAutomata::CellularAutomata (TileMap *tileMap) {
    m_tileMap = tileMap;

    Debug::log("INFO", "Init CellularAutomata.");

    init();
}

CellularAutomata::~CellularAutomata () {
    Debug::log("INFO", "Destroy CellularAutomata.");
    free();
}

void CellularAutomata::init () {
    SDL_Rect &tileMapRect = m_tileMap->getRect();

    size_t mapSize = tileMapRect.w * tileMapRect.h;

    m_output = new int [mapSize];
    m_state = new int [mapSize];
    memset(m_output, 0, mapSize * sizeof(int));
    memset(m_state, 0, mapSize * sizeof(int));

    for (int i = 0; i < mapSize; i++)
        m_state[i] = rand() % 2;

    auto set = [&](int x, int y, std::wstring s)
    {
        int p = 0;
        for (auto c : s)
        {
            m_state[y * tileMapRect.w + x + p] = c == L'#' ? 1 : 0;
            p++;
        }
    };

    
    // // R-Pentomino
    // set(80, 50, L"  ## ");
    // set(80, 51, L" ##  ");
    // set(80, 52, L"  #  ");

    // // Gosper Glider Gun
    // set(60, 45, L"........................#............");
    // set(60, 46, L"......................#.#............");
    // set(60, 47, L"............##......##............##.");
    // set(60, 48, L"...........#...#....##............##.");
    // set(60, 49, L"##........#.....#...##...............");
    // set(60, 50, L"##........#...#.##....#.#............");
    // set(60, 51, L"..........#.....#.......#............");
    // set(60, 52, L"...........#...#.....................");
    // set(60, 53, L"............##.......................");

    // // Infinite Growth
    // set(20, 50, L"########.#####...###......#######.#####");

    m_timer.start();
}

void CellularAutomata::free () {
    if (m_output) delete m_output;
    if (m_state) delete m_state;
}

void CellularAutomata::reset() {
    Debug::log("INFO", "Reset CellularAutomata.");

    free ();
    init ();
}

void CellularAutomata::updateTiles () {
    if (!m_timer.ifTimePassed(80))
        return;

    SDL_Rect &tileMapRect = m_tileMap->getRect();

    auto cell = [&](int x, int y)
    {
        return m_output[y * tileMapRect.w + x];
    };

    // Store output state
    for (int i = 0; i < tileMapRect.w * tileMapRect.h; i++)
        m_output[i] = m_state[i];
    
    for (int x = 0; x < tileMapRect.w; x++) {
        for (int y = 0; y < tileMapRect.h; y++)
        {
            // The secret of artificial life =================================================
            int nNeighbours =	cell(x - 1, y - 1) + cell(x - 0, y - 1) + cell(x + 1, y - 1) +
                                cell(x - 1, y + 0) +          0         + cell(x + 1, y + 0) +
                                cell(x - 1, y +	1) + cell(x + 0, y + 1) + cell(x + 1, y + 1);

            if (cell(x, y) == 1)
                m_state[y * tileMapRect.w + x] = nNeighbours == 2 || nNeighbours == 3;
            else
                m_state[y * tileMapRect.w + x] = nNeighbours == 3;
            // ===============================================================================

            std::unique_ptr<Tile>& tile = m_tileMap->getTile({x, y});

            if(tile) {
                // printf("x = %d; y = %d\n", x, y);

                if (cell(x, y) == 1)
                    // ncurses->drawChar(x, y, '1', NCurses::Colors::FG_WHITE_BG_BLACK);
                    tile->setID(Tile::GREEN);
                else
                    tile->setID(Tile::RED);
                    // ncurses->drawChar(x, y, '0', NCurses::Colors::FG_BLUE_BG_BLACK);
            }
        }
    }
}

// void CellularAutomata::draw() {
//     // clear();

//     // update(nCurses);

//     // attroff(COLOR_PAIR(0));
//     // refresh();
// }

// void CellularAutomata::input() {
//     // int ch = getch();

//     // switch (ch) {
//     //     // case KEY_UP: ui->changeID(Area::ROOM); break;
//     //     // case KEY_DOWN: ui->changeID(Area::ROOM_LEFT_DOOR); break;
//     //     // case KEY_LEFT: ui->changeID(Area::STAIRS_DOWN); break;
//     //     // case KEY_RIGHT: ui->changeID(Area::STAIRS_UP); break;

//     //     case 'q': 
//     //         loop = false;
//     // }
// }