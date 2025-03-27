#ifndef _TEST__H_
#define _TEST__H_

#include <SDL.h>
#include "defs.h"

class Wall
{
public:
    int x,y;
    SDL_Rect rect;
    bool active;
    Wall (int startX, int startY)
    {
        x=startX;
        y=startY;
        active=true;
        rect= {x,y,TILE_SIZE,TILE_SIZE};
    }
    void render(SDL_Renderer* renderer);
};



#endif // _TEST__H_

