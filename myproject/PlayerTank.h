#ifndef _PLAYERTANK__H_
#define _PLAYERTANK__H_

#include "defs.h"
#include "bullet.h"
#include <vector>
#include <algorithm>
#include "wall.h"
#include "graphics.h"
using namespace std;

class PlayerTank
{
public:
    int x,y;
    int dirX,dirY;
    SDL_Rect rect;
    vector<Bullet> bullets;
    PlayerTank() : x(0), y(0), dirX(0), dirY(-1), rect{0, 0, TILE_SIZE, TILE_SIZE} {}
    PlayerTank (int startX, int startY)
    {
        x = startX;
        y = startY;
        rect = {x,y,TILE_SIZE, TILE_SIZE};
        dirX=0;
        dirY=-1;
    }
    void move (int dx, int dy, const vector <Wall>& walls);
    void shoot();
    void updateBullets();
    void render (SDL_Renderer* renderer, SDL_Texture* texture);
};
#endif
