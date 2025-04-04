#include "EnemyTank.h"
void EnemyTank::move(const vector <Wall> walls)
    {
        if(--moveDelay>0) return;
        moveDelay=15;
        int newX=x+this->dirX, newY=y+this->dirY;
        SDL_Rect newRect = { newX, newY, TILE_SIZE, TILE_SIZE};
        int r=rand()%2;
        for (const auto& wall : walls)
        {
            if(wall.active &&SDL_HasIntersection(&newRect,&wall.rect))
            {
                if(r==0){
                    if (dirX==0&&dirY==-5) {
                        dirX=5; dirY=0;
                    }
                    else if (dirX==0&&dirY==5) {
                        dirX=-5; dirY=0;
                    }
                    else if (dirX==5&&dirY==0) {
                        dirX=0; dirY=5;
                    }
                    else if (dirX==-5&&dirY==0) {
                        dirX=0; dirY=-5;
                    }
                } else {
                    if (dirX==0&&dirY==-5) {
                        dirX=-5; dirY=0;
                    }
                    else if (dirX==0&&dirY==5) {
                        dirX=5; dirY=0;
                    }
                    else if (dirX==5&&dirY==0) {
                        dirX=0; dirY=-5;
                    }
                    else if (dirX==-5&&dirY==0) {
                        dirX=0; dirY=5;
                    }
                }
                return;
            }
        }
        if(newX>=TILE_SIZE&&newX<=SCREEN_WIDTH-TILE_SIZE*2&&newY>=TILE_SIZE&&newY<=SCREEN_HEIGHT-TILE_SIZE*2)
        {

            x=newX;
            y=newY;
            rect.x=x;
            rect.y=y;
        } else if(r==0){
            if (dirX==0&&dirY==-5) {
            dirX=5; dirY=0;
            }
            else if (dirX==0&&dirY==5) {
            dirX=-5; dirY=0;
            }
            else if (dirX==5&&dirY==0) {
            dirX=0; dirY=5;
            }
            else if (dirX==-5&&dirY==0) {
            dirX=0; dirY=-5;}
        }else if(r==1){
            if (dirX==0&&dirY==-5) {
                    dirX=-5; dirY=0;
                } else if (dirX==0&&dirY==5) {
                    dirX=5; dirY=0;
                } else if (dirX==5&&dirY==0) {
                        dirX=0; dirY=-5;
                } else if (dirX==-5&&dirY==0) {
                        dirX=0; dirY=5;
                }
        }
    }
    void EnemyTank::shoot()
    {
        if(--shootDelay>0) return;
        shootDelay=300 ;
        bullets.push_back(Bullet(x+TILE_SIZE/2-5,y+TILE_SIZE/2-5,this->dirX,this->dirY));
    }
    void EnemyTank::updateBullets()
    {
        for (auto &bullet : bullets)
        {
            bullet.move();
        }
        bullets.erase(remove_if(bullets.begin(),bullets.end(),[](Bullet &b){return !b.active;}),bullets.end());
    }
    void EnemyTank::render(SDL_Texture* enemy_tank_texture, SDL_Renderer* renderer)
    {
        SDL_Rect renderRect = {0,0,40,40};
        if(dirX==0&&dirY==-5) renderRect.x = 0;
        else if(dirX==5&&dirY==0) renderRect.x = 40;
        else if(dirX==0&&dirY==5) renderRect.x = 80;
        else if(dirX==-5&&dirY==0) renderRect.x = 120;
        blitRect(renderer,enemy_tank_texture,&renderRect,x,y);
        for (auto &bullet: bullets)
        {
            bullet.render(renderer);
        }
    }
