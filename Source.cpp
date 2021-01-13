#include "function_definitions.h"
#undef main
using namespace std;

void nastavitve(GameManager &igra);
void vec(GameManager& igra);
void overworld(GameManager& igra);

int main() {
    GameManager igra;
    igra.sound.toggle(); //samo za testing
    igra.init(igra);
    
    //igra.igralec.setName(); //izklopljeno za hitrejsi debugging

    SDL_Event event;
    SDL_PollEvent(&event);
    int pozicija_cursorja = 1;
    int izhod_switch = 0;
    Image main;
    Image cursor;

    while (!igra.keys[SDL_SCANCODE_ESCAPE] && event.type != SDL_QUIT) {
        SDL_PollEvent(&event);
        SDL_PumpEvents();
        SDL_RenderClear(igra.okno.renderer);
        main.init(igra.okno.renderer, "common/images/main.png", 0, 0, igra.okno.scalerCalculator(igra.okno.returnWindowWidth()), igra.okno.scalerCalculator(igra.okno.returnWindowHeight()));
        main.display(igra.okno.renderer);
        
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
            cursor.init(igra.okno.renderer, "common/images/cursor.png", igra.okno.scalerCalculator(20), igra.okno.scalerCalculator(120), igra.okno.scalerCalculator(98), igra.okno.scalerCalculator(49));
            cursor.display(igra.okno.renderer);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.zacni();
                SDL_RenderClear(igra.okno.renderer);
                //call za zacetek igre
                overworld(igra);
            }
            break;
        case 2:
            cursor.init(igra.okno.renderer, "common/images/cursor.png", igra.okno.scalerCalculator(20), igra.okno.scalerCalculator(180), igra.okno.scalerCalculator(98), igra.okno.scalerCalculator(49));
            cursor.display(igra.okno.renderer);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.vec();
                SDL_Delay(10);
                SDL_RenderClear(igra.okno.renderer);

                vec(igra);
            }
            break;
        case 3:
            cursor.init(igra.okno.renderer, "common/images/cursor.png", igra.okno.scalerCalculator(20), igra.okno.scalerCalculator(240), igra.okno.scalerCalculator(98), igra.okno.scalerCalculator(49));
            cursor.display(igra.okno.renderer);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.nastavitve();
                SDL_Delay(10);
                SDL_RenderClear(igra.okno.renderer);
                nastavitve(igra);
                pozicija_cursorja = 1;
            }
            break;
        case 4:
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.izhod();
                izhod_switch = 1;
            }
            cursor.init(igra.okno.renderer, "common/images/cursor.png", igra.okno.scalerCalculator(20), igra.okno.scalerCalculator(320), igra.okno.scalerCalculator(98), igra.okno.scalerCalculator(49));
            cursor.display(igra.okno.renderer);
            break;
        }
        SDL_RenderPresent(igra.okno.renderer);
        SDL_Delay(80);
        if (izhod_switch == 1) {
            break;
        }
    }
    //igra.sound.nasvidenje(); //greet
    SDL_DestroyWindow(igra.okno.window);
    SDL_FreeSurface(igra.okno.image);
    SDL_Quit();
    return 0;
}
