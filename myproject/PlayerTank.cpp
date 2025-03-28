#include "PlayerTank.h"
void PlayerTank::move (int dx, int dy, const vector <Wall>& walls)
    {
        int newX = x+dx;
        int newY= y+dy;
        this->dirX=dx;
        this->dirY=dy;
        SDL_Rect newRect = {newX, newY, TILE_SIZE, TILE_SIZE};
        for (int i=0; i<walls.size(); i++)
        {
            if (walls[i].active&&SDL_HasIntersection(&newRect, &walls[i].rect))
            {
                return; //ko cho đâm vào tường
            }
        }
        if ((newX>=TILE_SIZE&&newX<=SCREEN_WIDTH-TILE_SIZE*2)&&(newY>=TILE_SIZE&&newY<=SCREEN_HEIGHT-TILE_SIZE*2))
        {
            x=newX;
            y=newY;
            rect.x=x;
            rect.y=y;
        }//ko cho xe tang vuot ra ngoai man hinh
    }
    void PlayerTank::shoot()
    {
        bullets.push_back(Bullet(x+TILE_SIZE/2-5,y+TILE_SIZE/2-5,this->dirX,this->dirY));
    }
    void PlayerTank::updateBullets()
    {
        for (auto &bullet : bullets)
        {
            bullet.move();
        }
        bullets.erase(remove_if(bullets.begin(),bullets.end(),[](Bullet&b){return !b.active;}),bullets.end());
    }

    void PlayerTank::render (SDL_Renderer* renderer, SDL_Texture* texture)
    {
//        SDL_SetRenderDrawColor(renderer,255,255,0,255);
//        SDL_RenderFillRect(renderer,&rect);
        SDL_Rect renderRect = {0,0,40,40};
        if(dirX==0&&dirY==-5) renderRect.x = 0;
        else if(dirX==0&&dirY==5) renderRect.x = 80;
        else if(dirX==-5&&dirY==0) renderRect.x = 120;
        else if(dirX==5&&dirY==0) renderRect.x = 40;
        blitRect(renderer,texture,&renderRect,x,y);
        for (auto &bullet : bullets)
        {
            bullet.render(renderer);
        }
    }
