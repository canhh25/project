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
#include "graphics.h"
#include <SDL_mixer.h>
using namespace std;
class Game
{
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    vector <Wall> walls;
    PlayerTank player;
    int enemyNumber=5;
    vector<EnemyTank> enemies;
    void generateWalls();
    void spawnEnemies();
    SDL_Texture* texture;
    SDL_Texture* wallTexture;
    SDL_Texture* EnemyTankTexture;
    SDL_Texture* background;
    SDL_Texture* win;
    SDL_Texture* loose;
    SDL_Texture* startScreen;
    Mix_Chunk* shootSound;
    Mix_Music* gMusic;
    Mix_Chunk* explosion;
    Mix_Chunk* winSound;
    Mix_Chunk* looseSound;
    Mix_Music* waitMusic;
    bool isWinning = true;
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
        if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
            logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n",
            Mix_GetError() );
        }
        renderer =  createRenderer(window);
        generateWalls();
        player = PlayerTank(((MAP_WIDTH-1)/2)*TILE_SIZE,(MAP_HEIGHT-2)*TILE_SIZE);
        spawnEnemies();
        texture = loadTexture(renderer,"players_tank.png");
        wallTexture = loadTexture(renderer,"wall.png");
        EnemyTankTexture =loadTexture (renderer, "enemy_tank.png");
        background = loadTexture(renderer, "background.png");
        win = loadTexture(renderer, "win.png");
        loose = loadTexture (renderer, "loose.png");
        startScreen = loadTexture (renderer,"startScreen.png");
        shootSound = loadSound ("shootSound.wav");
        gMusic = loadMusic("gMusic.mp3");
        explosion = loadSound ("explosion.wav");
        winSound = loadSound("winSound.wav");
        looseSound = loadSound("looseSound.wav");
        waitMusic = loadMusic("waitMusic.mp3");
        Mix_VolumeMusic(25);
    }
    void update ();
    void render();
    void handleEvents();
    void run ();
    void GameEnd();
    void showStartScreen();
    ~Game()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_DestroyTexture(texture);
        SDL_DestroyTexture(EnemyTankTexture);
        SDL_DestroyTexture(wallTexture);
        SDL_DestroyTexture(startScreen);
        Mix_FreeChunk(shootSound);
        Mix_FreeChunk(explosion);
        Mix_FreeMusic(gMusic);
        Mix_FreeChunk(winSound);
        Mix_FreeChunk(looseSound);
        Mix_FreeMusic(waitMusic);
        SDL_Quit();
        Mix_Quit();
    }
};
#endif
