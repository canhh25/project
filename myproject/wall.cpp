#include "wall.h"
void Wall::render(SDL_Texture* wallTexture, SDL_Renderer* renderer)
    {
        if (active)
        {
            renderTexture(renderer,wallTexture,rect.x,rect.y);
        }
    }
