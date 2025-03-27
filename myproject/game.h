#ifndef _GAME__H_
#define _GAME__H_

#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <SDL.h>
#include "defs.h"
#include "wall.h"
#include "bullet.h"
#include "PlayerTank.h"
#include "EnemyTank.h"
#include <vector>
using namespace std;
class Game
{
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    vector <Wall> walls;
    PlayerTank player;
    int enemyNumber=3;
    vector<EnemyTank> enemies;
    void generateWalls();
    void spawnEnemies();
    Game ()
    {

        running = true;
        if (SDL_Init(SDL_INIT_VIDEO)<0)
        {
            cerr<<"SDL could not initialize! SDL_Error: "<< SDL_GetError()<<endl;
            running = false;
        }
        window = SDL_CreateWindow("Battle City", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if (!window)
        {
            cerr<<"Window could not be created! SDL_Error: "<< SDL_GetError()<<endl;
            running = false;
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer)
        {
            cerr<<" Renderer could not be created! SDL_Error: "<<SDL_GetError()<<endl;
            running = false;
        }
        generateWalls();
        player = PlayerTank(((MAP_WIDTH-1)/2)*TILE_SIZE,(MAP_HEIGHT-2)*TILE_SIZE);
        spawnEnemies();
    }
    void update ();
    void render();
    void handleEvents();
    void run ();
    ~Game()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};
#endif
