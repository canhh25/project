#include "game.h"
void Game::generateWalls()
{
    int a[15][20] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,0,0},
        {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
        {0,0,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,1,0,0},
        {0,0,1,1,1,0,0,0,1,1,0,0,0,1,1,1,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,1,1,0,0,1,1,1,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0},
        {0,0,1,0,0,1,1,1,0,0,0,0,0,1,1,0,0,0,1,0},
        {0,1,0,0,0,0,1,1,1,1,1,0,0,0,1,1,0,0,0,0},
        {0,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0},
        {0,1,1,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,0},
        {0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
    for(int y=0; y<15; y++)
        for(int x=0; x<20; x++)
            if(a[y][x]==1)
            {
                Wall w=Wall{x*TILE_SIZE,y*TILE_SIZE};
                walls.push_back(w);
            }
}
void Game::spawnEnemies()
{
    enemies.clear();
    for (int i=0; i<enemyNumber; i++)
    {
        int ex, ey;
        bool validPosition=false;
        while(!validPosition)
        {
            ex=(rand()%(MAP_WIDTH-2)+1)*TILE_SIZE;
            ey=(rand()%(MAP_HEIGHT-2)+1)*TILE_SIZE;
            validPosition=true;
            for (const auto&wall:walls)
            {
                if(wall.active&&wall.x==ex&&wall.y==ey)
                {
                    validPosition=false;
                    break;
                }
            }
        }
        enemies.push_back(EnemyTank(ex,ey));
    }
}
void Game::update ()
{
    player.updateBullets();
    for (auto& bullet : player.bullets)
    {
        for (auto&wall : walls)
        {
            if (wall.active&&SDL_HasIntersection(&bullet.rect,&wall.rect))
            {
                bullet.active=false;
                break;
            }
        }
    }
    for (auto& bullet : player.bullets)
    {
        for (auto& enemy : enemies)
        {
            if (enemy.active && SDL_HasIntersection(&bullet.rect, &enemy.rect))
            {
                play(explosion);
                enemy.active = false; // địch die
                bullet.active = false; // đạn biến mất
                break; // ko cho đạn xuyên qua
            }
        }
    }
    for (auto& enemy: enemies)
    {
        enemy.shoot();
        enemy.updateBullets();
    }
    for (auto& enemy: enemies)
    {
        for (auto& bullet: enemy.bullets)
        {
            for (auto& wall:walls)
            {
                if(wall.active&&SDL_HasIntersection(&bullet.rect,&wall.rect))
                {
                    bullet.active=false;
                    break;
                }
                if(SDL_HasIntersection(&bullet.rect,&player.rect))
                {
                    bullet.active = false;
                    play(explosion);
                }
            }
        }
    }
    enemies.erase(std::remove_if(enemies.begin(),enemies.end(),[](EnemyTank&e)
    {
        return !e.active;
    }),enemies.end());
    if(enemies.empty())
    {
        running=false;
        isWinning = true;
    }
}
void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if(event.type ==SDL_QUIT)
        {
            running = false;
        }
        else if (event.type==SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                player.move(0,-5,walls);
                break;
            case SDLK_DOWN:
                player.move(0,5,walls);
                break;
            case SDLK_RIGHT:
                player.move(5,0,walls);
                break;
            case SDLK_LEFT:
                player.move(-5,0,walls);
                break;
            case SDLK_SPACE:
                player.shoot();
                play(shootSound);
                break;
            case SDLK_9:  // Giảm âm lượng
                Mix_VolumeMusic(Mix_VolumeMusic(-1) - 16);
                break;
            case SDLK_0:  // Tăng âm lượng
                Mix_VolumeMusic(Mix_VolumeMusic(-1) + 16);
                break;
            }
        }
    }
}
void Game::render ()
{
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); //bouderies
    SDL_RenderClear(renderer); //delete color
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_Rect BGrect = {40,40,720,520};
    blitRect(renderer,background,&BGrect,40,40);
//        for (int i=1; i<MAP_HEIGHT-1; ++i)
//        {
//            for (int j=1; j<MAP_WIDTH-1; ++j)
//            {
//                SDL_Rect tile = {j * TILE_SIZE, i* TILE_SIZE, TILE_SIZE, TILE_SIZE};
//                SDL_RenderFillRect(renderer, &tile);
//            }
//        }
    for (int i=0; i<walls.size(); i++)
    {
        walls[i].render(wallTexture,renderer);
    }
    player.render(renderer,texture);
    for(auto& enemy:enemies)
    {
        enemy.render(enemy_tank_texture, renderer);
    }
    presentScene(renderer);
}
void Game::run ()
{
    play(gMusic);
    while (running)
    {
        for (auto& enemy: enemies)
        {
            enemy.move(walls);
            enemy.shoot();
        }

        handleEvents ();
        update();
        render();
        SDL_Delay(16);
    }
}
void Game::GameEnd()
{
    Mix_PauseMusic();
    if(isWinning)
    {
        renderTexture(renderer,win,0,0);
    }
    else
    {
        renderTexture(renderer,loose,0,0);
    }
    presentScene(renderer);
    SDL_Event event;
    bool waiting = true;
    while (waiting)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                waiting = false;
                running = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                waiting = false;
            }
        }
        SDL_Delay(16);
        SDL_Event event;
        bool isWaiting = true;
        while (isWaiting && running)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    isWaiting = false;
                    running = false;
                }
                else if (event.type == SDL_KEYDOWN)
                {
                    isWaiting = false;
                }
            }
            SDL_Delay(10);
        }
    }
}
