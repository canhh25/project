#include "wall.h"
void Wall::render(SDL_Texture* wallTexture, SDL_Renderer* renderer)
    {
        if (active)
        {
            //SDL_SetRenderDrawColor(renderer,150,75,0,255); //Brown
            //SDL_RenderFillRect(renderer,&rect);
            renderTexture(renderer,wallTexture,rect.x,rect.y);
        }
    }
