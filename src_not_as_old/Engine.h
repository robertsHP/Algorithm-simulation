#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SDL.h"
#include "SDL_image.h"
#include "DataTypes.h"
#include "Objects.h"

////////////////////////////////////////////////////////////////////////////
/*
    GLOBAL DATA
*/
////////////////////////////////////////////////////////////////////////////

    #define WINDOW_TITLE "Chess"

    struct GameVisualData {
        SDL_Window*     win;
        SDL_Renderer*   rend;
        unsigned int    w, h;
    } g_win;

    bool g_loopOn;
    bool g_exitCond;

    bool game_Loop ();
    bool game_Init ();
    bool game_LoadVideo ();
    void game_FreeVideo ();
    void game_Free ();
    void game_Input (SDL_Event *event);

////////////////////////////////////////////////////////////////////////////
/*
    CURSOR DATA
*/
////////////////////////////////////////////////////////////////////////////

    #define CURSOR_W 17
    #define CURSOR_H 15

    typedef enum {
        STATE_CURSOR_DEFAULT = 1,
        STATE_CURSOR_LOADING
    } CursorState;

    struct Cursor {
        GPUSheet        sheet;
        SDL_Rect        rect;
        CursorState     state;
    } g_cursor;

    void cursor_Create ();
    void cursor_Free ();
    void cursor_Draw ();

////////////////////////////////////////////////////////////////////////////
/*
    STATE MANAGER

    -StateID - identification for states. Max available amount is 12 starting
    from STATE_MIN and and ending with STATE_MAX
    -State - a data structure that contains function pointers that are based
    on the set StateID.
*/
////////////////////////////////////////////////////////////////////////////

    typedef enum {
            STATE_MENU = 0,
            STATE_GAME,
        STATE_MAX
    } StateID;

    typedef struct {
        StateID   id;
        bool      updating;
        bool      hidden;
        bool      paused;
        void    (*stateTerm)(); //State termination function
        void    (*input)(SDL_Event* event);
        void    (*update)();
        void    (*draw)();
    } State;

    void state_Init (StateID id);
    void state_SetNewState (StateID id);
    void state_Hide (StateID id, bool cond);
    void state_Pause (StateID id, bool cond);
    bool state_IsInitiated (StateID id);

    State g_states[STATE_MAX];

    void stCont_UpdateStateStatus (StateID id);
    void stCont_PerformStateOperations (StateID id);
