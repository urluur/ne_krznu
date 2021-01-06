#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <windows.h>
#include <MMSystem.h>
#include "function_definitions.h"
#undef main
using namespace std;
SDL_Window* window=NULL;
SDL_Surface* surface=NULL;
SDL_Surface* image=NULL;

const int Window_width = 720;
const int Window_height = 640;
const Uint8* keys = SDL_GetKeyboardState(NULL);

void cleanUp() {
    SDL_DestroyWindow(window);
    SDL_FreeSurface(image);
    SDL_Quit();
}

int init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Init, Error: %d", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("NE krznu -urlu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Window_width, Window_height, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("SDL Create Window, Error: %d", SDL_GetError());
        return -1;
    }

    surface = SDL_GetWindowSurface(window);
    srand(time(NULL));
    return 0;
}

int main() {
    init();
    SDL_Event event;
    SDL_PollEvent(&event);
    int pozicija_cursorja = 1;
    int izhod_switch = 0;
    while (!keys[SDL_SCANCODE_ESCAPE] && event.type != SDL_QUIT) {
        SDL_PollEvent(&event);
        SDL_PumpEvents();
        if (keys[SDL_SCANCODE_UP]) {
            sound_cursorMove();
            if (pozicija_cursorja == 1) {
                pozicija_cursorja = 4;
            }
            else {
                pozicija_cursorja--;
            }
        }
        else if (keys[SDL_SCANCODE_DOWN]) {
            sound_cursorMove();
            if (pozicija_cursorja == 4)
            {
                pozicija_cursorja = 1;
            }
            else
            {
                pozicija_cursorja++;
            }
        }
        switch (pozicija_cursorja) {
        case 1:
            image = SDL_LoadBMP("main_zacni.bmp");
            break;
        case 2:
            image = SDL_LoadBMP("main_vec.bmp");
            break;
        case 3:
            image = SDL_LoadBMP("main_nastavitve.bmp");
            break;
        case 4:
            if (keys[SDL_SCANCODE_RETURN]) {
                izhod_switch = 1;
            }
            image = SDL_LoadBMP("main_izhod.bmp");
            break;
        }
        SDL_UpdateWindowSurface(window);
        SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));
        SDL_BlitSurface(image, NULL, surface, NULL);
        SDL_Delay(80);
        if (izhod_switch == 1) {
            break;
        }
    }
    sound_oof();
    cleanUp();
    return 0;
}
