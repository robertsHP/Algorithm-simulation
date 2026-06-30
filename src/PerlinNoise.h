#pragma once

#include "TileMap.h"
#include "Timer.h"

class PerlinNoise {
    private:
        TileMap *m_tileMap;
        Timer m_timer;

    public:
        PerlinNoise (TileMap *tileMap);
        ~PerlinNoise ();

    private:
        void init ();
        void free ();

    public:
        // void reset ();
        void updateTiles ();
        // void draw();
        // void input();
};

