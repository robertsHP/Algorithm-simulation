#pragma once

#include <iostream>
#include <cstdlib>
#include <cstring>

#include <memory>

#include "TileMap.h"
#include "Timer.h"

class CellularAutomata {
    private:
        int *m_output;
        int *m_state;

        TileMap *m_tileMap;
        Timer m_timer;

    public:
        CellularAutomata (TileMap *tileMap);
        ~CellularAutomata ();

    private:
        void init ();
        void free ();

    public:
        void reset ();
        void updateTiles ();
        // void draw();
        // void input();
};


