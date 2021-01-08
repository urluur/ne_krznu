#include "function_definitions.h"
#undef main
using namespace std;

const int Window_width = 720;
const int Window_height = 640;
const Uint8* keys = SDL_GetKeyboardState(NULL);

int init(GameManager &igra);
void nastavitve(GameManager &igra);

int main() {
    GameManager igra;
    init(igra);
    igra.igralec.setName();
    SDL_Event event;
    SDL_PollEvent(&event);
    int pozicija_cursorja = 1;
    int izhod_switch = 0;
    while (!keys[SDL_SCANCODE_ESCAPE] && event.type != SDL_QUIT) {
        SDL_PollEvent(&event);
        SDL_PumpEvents();
        if (keys[SDL_SCANCODE_UP]) {
            igra.zvok.sound.cursorMove();
            if (pozicija_cursorja == 1) {
                pozicija_cursorja = 4;
            }
            else { pozicija_cursorja--; }
        }
        else if (keys[SDL_SCANCODE_DOWN]) {
            igra.zvok.sound.cursorMove();
            if (pozicija_cursorja == 4) { pozicija_cursorja = 1; }
            else { pozicija_cursorja++;}
        }
        SDL_FreeSurface(igra.okno.image);
        switch (pozicija_cursorja) {
        case 1:
            igra.okno.image = SDL_LoadBMP("common/images/main_zacni.bmp");
            if (keys[SDL_SCANCODE_RETURN]) {
                igra.zvok.sound.zacni();

            }
            break;
        case 2:
            igra.okno.image = SDL_LoadBMP("common/images/main_vec.bmp");
            if (keys[SDL_SCANCODE_RETURN]) {
                igra.zvok.sound.vec();

            }
            break;
        case 3:
            igra.okno.image = SDL_LoadBMP("common/images/main_nastavitve.bmp");
            if (keys[SDL_SCANCODE_RETURN]) {
                igra.zvok.sound.nastavitve();
                SDL_Delay(10);
                nastavitve(igra);
                pozicija_cursorja = 1;
            }
            break;
        case 4:
            if (keys[SDL_SCANCODE_RETURN]) {
                igra.zvok.sound.izhod();
                izhod_switch = 1;
            }
            igra.okno.image = SDL_LoadBMP("common/images/main_izhod.bmp");
            break;
        }
        SDL_UpdateWindowSurface(igra.okno.window);
        SDL_BlitSurface(igra.okno.image, NULL, igra.okno.surface, NULL);
        SDL_Delay(80);
        if (izhod_switch == 1) {
            break;
        }
    }
    igra.zvok.sound.nasvidenje();
    igra.zvok.sound.oof();
    SDL_DestroyWindow(igra.okno.window);
    SDL_FreeSurface(igra.okno.image);
    SDL_Quit();
    return 0;
}

int init(GameManager &igra) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL Init, Error: %d", SDL_GetError());
        return -1;
    }
    igra.okno.window = SDL_CreateWindow("NE krznu -urlu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Window_width, Window_height, SDL_WINDOW_SHOWN);
    if (igra.okno.window == NULL) {
        printf("SDL Create Window, Error: %d", SDL_GetError());
        return -1;
    }
    igra.okno.surface = SDL_GetWindowSurface(igra.okno.window);
    srand(time(NULL));
    return 0;
}
void nastavitve(GameManager &igra) {
    SDL_Event ev_nastavitve;
    int main = 0;
    int pozicija_cursorja = 1;
    while (main == 0) {
        SDL_PollEvent(&ev_nastavitve);
        SDL_PumpEvents();
        if (keys[SDL_SCANCODE_UP]) {
            igra.zvok.sound.cursorMove();
            if (pozicija_cursorja == 1) {
                pozicija_cursorja = 4;
            }
            else { pozicija_cursorja--; }
        }
        else if (keys[SDL_SCANCODE_DOWN]) {
            igra.zvok.sound.cursorMove();
            if (pozicija_cursorja == 4) { pozicija_cursorja = 1; }
            else { pozicija_cursorja++; }
        }
        SDL_FreeSurface(igra.okno.image);
        switch (pozicija_cursorja) {
        case 1:
            igra.okno.image = SDL_LoadBMP("common/images/set_dimenzije.bmp");
            if (keys[SDL_SCANCODE_RETURN]) {
                igra.zvok.sound.dimenzije();

            }
            break;
        case 2:
            igra.okno.image = SDL_LoadBMP("common/images/set_ime.bmp");
            if (keys[SDL_SCANCODE_RETURN]) {
                igra.zvok.sound.spremeni_ime();
                igra.igralec.setName();
            }
            break;
        case 3:
            igra.okno.image = SDL_LoadBMP("common/images/set_zvok.bmp");
            if (keys[SDL_SCANCODE_RETURN]) {
                igra.zvok.sound.spremeni_zvok();
                igra.zvok.sound.toggle();
            }
            
            break;
        case 4:
            igra.okno.image = SDL_LoadBMP("common/images/set_nazaj.bmp");
            if (keys[SDL_SCANCODE_RETURN]) {
                igra.zvok.sound.nazaj();
                main = 1;
            }
            break;
        }
        if (!(!keys[SDL_SCANCODE_ESCAPE] || ev_nastavitve.type != SDL_QUIT)) {
            main = 1;
        }
        SDL_UpdateWindowSurface(igra.okno.window);
        SDL_BlitSurface(igra.okno.image, NULL, igra.okno.surface, NULL);
        SDL_Delay(80);
    }
    igra.zvok.sound.oof();
}