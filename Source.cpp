#include "function_definitions.h"

#undef main
using namespace std;

void nastavitve(GameManager &igra);
void vec(GameManager& igra);
void overworld(GameManager& igra);

int main() {
    GameManager igra;
    {
        bool problemi = igra.init();
        if (problemi) {
            return EXIT_FAILURE;
        }
    }
    //igra.sound.toggle(); //samo za testing
    //igra.igralec.setName(); //izklopljeno za hitrejsi debugging

    SDL_Event event;
    SDL_PollEvent(&event);
    short pozicija_cursorja = 1;
    bool izhod_switch = false;
    Image main;
    Image cursor;

    while (!igra.keys[SDL_SCANCODE_ESCAPE] && event.type != SDL_QUIT) {
        SDL_PollEvent(&event);
        SDL_PumpEvents();
        SDL_RenderClear(igra.okno.ren);
        main.init(igra.okno.ren, "common/img/main.png", 0, 0, igra.okno.scaleCal(igra.okno.returnWindowWidth()), igra.okno.scaleCal(igra.okno.returnWindowHeight()));
        main.display(igra.okno.ren);
        
        if (igra.keys[SDL_SCANCODE_UP]) {
            igra.sound.cursorMove();
            if (pozicija_cursorja == 1) {
                pozicija_cursorja = 4;
            }
            else { pozicija_cursorja--; }
        }
        else if (igra.keys[SDL_SCANCODE_DOWN]) {
            igra.sound.cursorMove();
            if (pozicija_cursorja == 4) { pozicija_cursorja = 1; }
            else { pozicija_cursorja++;}
        }
        switch (pozicija_cursorja) {
        case 1:
            cursor.init(igra.okno.ren, "common/img/cursor.png", igra.okno.scaleCal(20), igra.okno.scaleCal(120), igra.okno.scaleCal(98), igra.okno.scaleCal(49));
            cursor.display(igra.okno.ren);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.zacni();
                SDL_RenderClear(igra.okno.ren);
                overworld(igra);
            }
            break;
        case 2:
            cursor.init(igra.okno.ren, "common/img/cursor.png", igra.okno.scaleCal(20), igra.okno.scaleCal(180), igra.okno.scaleCal(98), igra.okno.scaleCal(49));
            cursor.display(igra.okno.ren);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.vec();
                SDL_Delay(10);
                SDL_RenderClear(igra.okno.ren);

                vec(igra);
            }
            break;
        case 3:
            cursor.init(igra.okno.ren, "common/img/cursor.png", igra.okno.scaleCal(20), igra.okno.scaleCal(240), igra.okno.scaleCal(98), igra.okno.scaleCal(49));
            cursor.display(igra.okno.ren);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.nastavitve();
                SDL_Delay(10);
                SDL_RenderClear(igra.okno.ren);
                nastavitve(igra);
                pozicija_cursorja = 1;
            }
            break;
        case 4:
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.izhod();
                izhod_switch = true;
            }
            cursor.init(igra.okno.ren, "common/img/cursor.png", igra.okno.scaleCal(20), igra.okno.scaleCal(320), igra.okno.scaleCal(98), igra.okno.scaleCal(49));
            cursor.display(igra.okno.ren);
            break;
        }
        SDL_RenderPresent(igra.okno.ren);
        SDL_Delay(80);
        if (izhod_switch) {
            break;
        }
    }
    //igra.sound.nasvidenje(); //greet
    SDL_DestroyWindow(igra.okno.window);
    SDL_FreeSurface(igra.okno.image);
    SDL_Quit();
    return EXIT_SUCCESS;
}
