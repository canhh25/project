#ifndef _BULLET__H_
#define _BULLET__H_

#include <SDL.h>
#include "defs.h"
#include "graphics.h"
class Bullet
{
public:
    int x,y;
    int dx, dy;
    SDL_Rect rect;
    bool active;
    Bullet (int startX, int startY, int dirX, int dirY)
    {
        x=startX;
        y=startY;
        dx=dirX;
        dy=dirY;
        active=true;
        rect= { x, y, 10, 10};
    }
    void move();
    void render(SDL_Renderer* renderer);
};

#endif _BULLET__H_
