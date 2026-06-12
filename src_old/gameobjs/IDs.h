#pragma once

enum GameObjID : unsigned int {
    ////////TILES///////////
        //Ground
            T_DEFAULT       = 0,
            T_GRASSNORMAL   = 1,
    T_LAST,
    ////////ENTITIES//////////
        //Player
            E_P_SOLDIER     = 1000,
            E_P_SAPPER      = 1001,
            E_P_MEDIC       = 1002,
            E_P_TANK        = 1003,
        //Enemies
            E_EN_SOLDIER    = 1004,
            E_EN_SAPPER     = 1005,
            E_EN_MEDIC      = 1006,
            E_EN_TANK       = 1007,
    E_LAST
};

enum InvItemID : unsigned int {

    I_LAST
};
