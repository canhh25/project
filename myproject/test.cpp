#include "test.h"

void Wall::render(SDL_Renderer* renderer)
    {
        if (active)
        {
            SDL_SetRenderDrawColor(renderer,150,75,0,255); //Brown
            SDL_RenderFillRect(renderer,&rect);
        }
    }
