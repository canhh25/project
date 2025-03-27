#include "bullet.h"
void Bullet::move()
    {
        x+=dx;
        y+=dy;
        rect.x=x;
        rect.y=y;
        if(x<TILE_SIZE||x>SCREEN_WIDTH-TILE_SIZE||y<TILE_SIZE||y>SCREEN_HEIGHT-TILE_SIZE) active=false; //ra ngoài màn hình = xóa
    }
    void Bullet::render(SDL_Renderer* renderer)
    {
        if(active)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer,&rect);
        }
    }
