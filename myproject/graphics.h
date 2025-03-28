#ifndef _GRAPHICS__H_
#define _GRAPHICS__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "defs.h"


    void logErrorAndExit(const char* msg, const char* error);

    SDL_Renderer* createRenderer(SDL_Window* window);

    void prepareScene(SDL_Renderer* renderer, SDL_Texture *background);

    void presentScene(SDL_Renderer* renderer);

    SDL_Texture *loadTexture(SDL_Renderer* renderer, const char *filename);

    void renderTexture(SDL_Renderer* renderer, SDL_Texture *texture, int x, int y);

    void blitRect(SDL_Renderer* renderer, SDL_Texture *texture, SDL_Rect *src, int x, int y);

#endif
