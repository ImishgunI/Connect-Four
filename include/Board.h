#pragma once

#include <SDL2/SDL.h>
#include <array>

class Board{
private:
    static SDL_Window* window;
    static bool quit;
    static SDL_Event event;
    static SDL_Renderer* renderer;

public:

    static int createWindow();

    static void renderBoard(SDL_Renderer* renderer);

};
