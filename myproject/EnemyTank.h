#ifndef _ENEMYTANK__H_
#define _ENEMYTANK__H_

#include <SDL.h>
#include "defs.h"
#include "bullet.h"
#include <vector>
#include <algorithm>
#include "wall.h"
#include <SDL_mixer.h>
#include "graphics.h"
#include "PlayerTank.h"

using namespace std;
class EnemyTank
{
public:
    int x,y, dirX, dirY, moveDelay, shootDelay;
    SDL_Rect rect;
    bool active;
    vector<Bullet> bullets;
    EnemyTank(int startX, int startY)
    {
        moveDelay=15;
        shootDelay=30;
        x=startX;
        y=startY;
        rect= {x,y,TILE_SIZE,TILE_SIZE};
        int r=rand()%4;
        if(r==0){
            dirX=0; dirY=5;
        }
        if(r==1){
            dirX=0;dirY=-5;
        }
        if(r==2){
            dirX=5;dirY=0;
        }
        if(r==3){
            dirX=-5; dirY=0;
        }
        active=true;
    }
    void move(const vector <Wall> walls);
    void shoot();
    void updateBullets();
    void render(SDL_Texture* enemy_tank_texture ,SDL_Renderer* renderer);
};
#endif
