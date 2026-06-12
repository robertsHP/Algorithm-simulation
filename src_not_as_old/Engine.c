#include "Engine.h"
#include "GameState.h"

bool game_Loop () {
    g_exitCond = -1;
    g_allocInfo.allocCount = 0;
    g_allocInfo.freeCount = 0;

    if(game_Init()) {
        const int       FRAME_DELAY = 1000 / 60;
        Uint32          frameStart;
        int             frameTime;

        fonts_Load();
        cursor_Create();
        state_Init(STATE_GAME);

        while(g_loopOn){
            frameStart = SDL_GetTicks();

            SDL_RenderClear(g_win.rend);
            for(size_t i = 0; i < STATE_MAX; ++i) {
                stCont_UpdateStateStatus(i);
                stCont_PerformStateOperations(i);
            }
            cursor_Draw();
            SDL_RenderPresent(g_win.rend);

            frameTime = SDL_GetTicks() - frameStart;
            if(FRAME_DELAY > frameTime){
                SDL_Delay(FRAME_DELAY - frameTime);
            }
        }
    }
    game_Free();
    return g_exitCond;
}
bool game_Init () {
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        if(IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG) {
            if(game_LoadVideo()){
                return true;
            } else printf("game_Init : Game failed to load video.\n");
        } else printf("game_Init : SDL_image Could not initialize! IMG_Error: %s.\n", IMG_GetError());
    } else printf("game_Init : SDL2 Could not initialize! SDL_Error: %s.\n", SDL_GetError());
    return false;
}
bool game_LoadVideo () {
    g_win.w = 800;
    g_win.h = 600;
    g_win.win = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        g_win.w,
        g_win.h,
        SDL_WINDOW_SHOWN
    );
    if (g_win.win){
        g_win.rend = SDL_CreateRenderer(g_win.win, -1, 0);
        if (g_win.rend){
            g_loopOn = true;
            return true;
        } else printf("game_LoadVideo : Game failed to create the renderer.\n");
    } else printf("game_LoadVideo : Game Failed to create the window.\n");
    return false;
}
void game_FreeVideo () {
    if(g_win.rend) SDL_DestroyRenderer(g_win.rend);
    if(g_win.win) SDL_DestroyWindow(g_win.win);
}
void game_Free () {
    State *state;

    for(size_t i = 0; i < STATE_MAX; ++i) {
        if(state_IsInitiated(i)) {
            state = &g_states[i];
            (*state->stateTerm)();
        }
    }
    cursor_Free();
    fonts_Free();
    game_FreeVideo();
    SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
    IMG_Quit();
    SDL_Quit();
}
void game_Input (SDL_Event *event) {
    switch(event->type){
        case SDL_QUIT :
            g_exitCond = 0;
            g_loopOn = false;
            break;
        case SDL_MOUSEMOTION :
            SDL_GetMouseState(&g_cursor.rect.x, &g_cursor.rect.y);
        default : break;
    }
}

void cursor_Create () {
    SDL_ShowCursor(SDL_DISABLE);
    g_cursor.state = STATE_CURSOR_DEFAULT;
    GPUSh_Create(&g_cursor.sheet, "gfx/cursor.png", SDL_POINT(CURSOR_W, CURSOR_H));
    GPUSh_RemoveColor(&g_cursor.sheet, SDL_COLOR(255,0,255,255));
    g_cursor.rect = SDL_RECT(0, 0, CURSOR_W, CURSOR_H);
}
void cursor_Free () {
    GPUSh_Free(&g_cursor.sheet);
}
void cursor_Draw () {
    SDL_RenderCopyEx(
        g_win.rend,
        g_cursor.sheet.textr,
        &g_cursor.sheet.tmplts[g_cursor.state],
        &g_cursor.rect,
        0,
        NULL,
        SDL_FLIP_NONE
    );
}

void state_Init (StateID id) {
    state_SetNewState(id);
    g_states[id].paused = false;
    g_states[id].hidden = false;
}
void state_SetNewState (StateID id) {
    if(id >= 0 || id <= STATE_MAX) {
        g_states[id].id = id;
        g_states[id].updating = true;
    } else printf("state_SetNewState : Selected State failed to change state because the passed id is out of enum bounds.");
}
void state_Hide (StateID id, bool cond) {
    g_states[id].paused = cond;
    g_states[id].hidden = cond;
}
void state_Pause (StateID id, bool cond) {
    g_states[id].paused = cond;
}
bool state_IsInitiated (StateID id) {
    return g_states[id].stateTerm != NULL;
}
void stCont_UpdateStateStatus (StateID id) {
    State *state = &g_states[id];
    if(&state->updating != NULL) {
        if(state->updating) {
            if(state_IsInitiated(id))
                (*state->stateTerm)();
            switch (state->id){
                case STATE_GAME : gameState_Init(state); break;
                default : break;
            }
            state->updating = false;
        }
    }
}
void stCont_PerformStateOperations (StateID id) {
    State *state = &g_states[id];
    if(state_IsInitiated(id) && !state->hidden) {
        if(!state->paused) {
            SDL_Event event;
            while(SDL_PollEvent(&event)){
                game_Input(&event);
                (*state->input)(&event);
            }
            (*state->update)();
        }
        (*state->draw)();
    }
}
