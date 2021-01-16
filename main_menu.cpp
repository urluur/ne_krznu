#include "main_menu.h"
using namespace std;

void overworld(GameManager& igra) {
    SDL_RenderClear(igra.okno.renderer);
    SDL_Event ev_overworld;
    int main = 0;
    int level_igralca = 1;
    Image img_overworld;
    Image img_player;
    Image img_drevo;
    Image imgs_farma[5];
    Image img_zastavica_fullscreen;
    Image img_press_enter;
    int blink = 0;

    int level_clear=0;
    img_overworld.init(igra.okno.renderer, "common/images/overworld.png", 0, 0, igra.okno.scalerCalculator(igra.okno.returnWindowWidth()), igra.okno.scalerCalculator(igra.okno.returnWindowHeight()));
    img_overworld.display(igra.okno.renderer);
     
    int x=90, y=160;
    int final_x, final_y;
    bool x_bool=false, y_bool=false;

    while (main == 0) {
        SDL_Delay(500);
        SDL_PollEvent(&ev_overworld);
        SDL_PumpEvents();
        SDL_RenderClear(igra.okno.renderer);
        img_overworld.init(igra.okno.renderer, "common/images/overworld.png", 0, 0, igra.okno.scalerCalculator(igra.okno.returnWindowWidth()), igra.okno.scalerCalculator(igra.okno.returnWindowHeight()));
        img_overworld.display(igra.okno.renderer);
        narisiFarmeAliDosezke(igra, level_clear);
        SDL_RenderPresent(igra.okno.renderer);

        switch (level_clear) {
        case 0:
            img_player.init(igra.okno.renderer, "common/images/player.png", igra.okno.scalerCalculator(55), igra.okno.scalerCalculator(160), igra.okno.scalerCalculator(29), igra.okno.scalerCalculator(64));
            img_player.display(igra.okno.renderer);
            img_press_enter.init(igra.okno.renderer, "common/images/pressreturn.png", 0, 0, igra.okno.scalerCalculator(igra.okno.returnWindowWidth()), igra.okno.scalerCalculator(igra.okno.returnWindowHeight()));
            haltEnter(igra, img_press_enter, ev_overworld, 0);
            animacija(igra, 1);
            premakniNaXY(igra, x, y, 180, 160, img_overworld, img_player, 0);

            haltEnter(igra, img_press_enter, ev_overworld, 0);

            cout << "Prvi nivo" << endl;
            //level_clear = level1();
            level_clear = 1;
            break;
        case 1:
            img_press_enter.init(igra.okno.renderer, "common/images/pressreturn.png", 0, 0, igra.okno.scalerCalculator(igra.okno.returnWindowWidth()), igra.okno.scalerCalculator(igra.okno.returnWindowHeight()));

            premakniNaXY(igra, x, y, 90, 250, img_overworld, img_player, level_clear);
            animacija(igra, 2);
            premakniNaXY(igra, x, y, 165, 350, img_overworld, img_player, level_clear);
            haltEnter(igra, img_press_enter, ev_overworld, 1);

            cout << "Drugi nivo" << endl;
            //level_clear = level2();
            level_clear = 2;
            break;
        case 2:
            premakniNaXY(igra, x, y, 200, 450, img_overworld, img_player, level_clear);
            premakniNaXY(igra, x, y, 350, 450, img_overworld, img_player, level_clear);
            haltEnter(igra, img_press_enter, ev_overworld, 2);
            animacija(igra, 3);

            cout << "Tretji nivo" << endl;
            //level_clear = level3();
            level_clear = 3;
            break;
        case 3:
            premakniNaXY(igra, x, y, 466, 240, img_overworld, img_player, level_clear);
            haltEnter(igra, img_press_enter, ev_overworld, 3);
            //animacija(igra, 4);

            cout << "Cetrti nivo" << endl;
            //level_clear = level4();
            level_clear = 4;
            break;
        case 4:
            //animacija(igra, 5);
            premakniNaXY(igra, x, y, 420, 100, img_overworld, img_player, level_clear);
            haltEnter(igra, img_press_enter, ev_overworld, 4);

            cout << "Peti nivo" << endl;
            //level_clear = level5();
            level_clear = 5;
            break;
        case 5:
            premakniNaXY(igra, x, y, 425, 30, img_overworld, img_player, level_clear);
            haltEnter(igra, img_press_enter, ev_overworld, 4);

            cout << "Zmaga!" << endl;
            img_overworld.init(igra.okno.renderer, "common/images/overworld.png", 0, 0, igra.okno.scalerCalculator(igra.okno.returnWindowWidth()), igra.okno.scalerCalculator(igra.okno.returnWindowHeight()));
            img_overworld.display(igra.okno.renderer);
            img_player.init(igra.okno.renderer, "common/images/player.png", igra.okno.scalerCalculator(x), igra.okno.scalerCalculator(y), igra.okno.scalerCalculator(29), igra.okno.scalerCalculator(64));
            img_player.display(igra.okno.renderer);
            img_zastavica_fullscreen.init(igra.okno.renderer, "common/images/zastavica_fullscreen.png", 0, 0, igra.okno.scalerCalculator(igra.okno.returnWindowWidth()), igra.okno.scalerCalculator(igra.okno.returnWindowHeight()));
            img_zastavica_fullscreen.display(igra.okno.renderer);
            narisiFarmeAliDosezke(igra, level_clear);
            SDL_RenderPresent(igra.okno.renderer);

            //prikaz rekordov
            SDL_Delay(3000);
            main = 1;
            break;
        default:
            cout << "Error: level_clear" << endl;
        }
        SDL_RenderPresent(igra.okno.renderer);

        if ((igra.keys[SDL_SCANCODE_ESCAPE] || ev_overworld.type == SDL_QUIT)) {
            main = 1;
            //zasilno shranjevanje podatkov
        }
    }
    SDL_RenderClear(igra.okno.renderer);
    //shranjevanje recordov
}

void nastavitve(GameManager& igra) {
    SDL_RenderClear(igra.okno.renderer);
    SDL_Event ev_nastavitve;
    SDL_Delay(200);
    SDL_PollEvent(&ev_nastavitve);
    int main = 0;
    int pozicija_cursorja = 1;
    Image img_nastavitve;
    Image cursor;
    while (main == 0)
    {
        SDL_PollEvent(&ev_nastavitve);
        SDL_PumpEvents();
        SDL_RenderClear(igra.okno.renderer);
        img_nastavitve.init(igra.okno.renderer, "common/images/nastavitve.png", 0, 0, igra.okno.scalerCalculator(igra.okno.returnWindowWidth()), igra.okno.scalerCalculator(igra.okno.returnWindowHeight()));
        img_nastavitve.display(igra.okno.renderer);
        if (igra.keys[SDL_SCANCODE_UP])
        {
            igra.sound.cursorMove();
            if (pozicija_cursorja == 1) {
                pozicija_cursorja = 4;
            }
            else {
                pozicija_cursorja--;
            }
        }
        else if (igra.keys[SDL_SCANCODE_DOWN])
        {
            igra.sound.cursorMove();
            if (pozicija_cursorja == 4) { pozicija_cursorja = 1; }
            else { pozicija_cursorja++; }
        }

        SDL_FreeSurface(igra.okno.image);

        switch (pozicija_cursorja)
        {
        case 1:
            cursor.init(igra.okno.renderer, "common/images/cursor.png", igra.okno.scalerCalculator(20), igra.okno.scalerCalculator(210), igra.okno.scalerCalculator(98), igra.okno.scalerCalculator(49));
            cursor.display(igra.okno.renderer);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.dimenzije();
                cout << "spreminjam velikost okna" << endl;
                igra.okno.toggleScaler();
                SDL_SetWindowSize(igra.okno.window, igra.okno.scalerCalculator(igra.okno.returnWindowWidth()), igra.okno.scalerCalculator(igra.okno.returnWindowHeight()));
                if (igra.okno.vrniScaler() == 100) {
                    SDL_SetWindowFullscreen(igra.okno.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                }
                else {
                    SDL_SetWindowFullscreen(igra.okno.window, 0);
                }
                
                
            }
            break;
        case 2:
            cursor.init(igra.okno.renderer, "common/images/cursor.png", igra.okno.scalerCalculator(20), igra.okno.scalerCalculator(310), igra.okno.scalerCalculator(98), igra.okno.scalerCalculator(49));
            cursor.display(igra.okno.renderer);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.spremeni_ime();
                igra.igralec.setName();
            }
            break;
        case 3:
            cursor.init(igra.okno.renderer, "common/images/cursor.png", igra.okno.scalerCalculator(20), igra.okno.scalerCalculator(420), igra.okno.scalerCalculator(98), igra.okno.scalerCalculator(49));
            cursor.display(igra.okno.renderer);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.spremeni_zvok();
                igra.sound.toggle();
            }

            break;
        case 4:
            cursor.init(igra.okno.renderer, "common/images/cursor.png", igra.okno.scalerCalculator(20), igra.okno.scalerCalculator(510), igra.okno.scalerCalculator(98), igra.okno.scalerCalculator(49));
            cursor.display(igra.okno.renderer);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.nazaj();
                main = 1;
            }
            break;
        }

        if (!(!igra.keys[SDL_SCANCODE_ESCAPE] || ev_nastavitve.type != SDL_QUIT)) {
            main = 1;
        }

        SDL_RenderPresent(igra.okno.renderer);
        SDL_Delay(75);
    }

    //igra.sound.oof();
}
void vec(GameManager& igra) {
    SDL_Delay(200);
    SDL_Event ev_vec;
    SDL_PollEvent(&ev_vec);
    int main = 0;
    int pozicija_cursorja = 1;
    Image img_vec;
    Image cursor;
    Image github(igra.okno.renderer, "common/images/github.png", igra.okno.scalerCalculator(20), igra.okno.scalerCalculator(20), igra.okno.scalerCalculator(279), igra.okno.scalerCalculator(66));
    while (main == 0)
    {
        SDL_PollEvent(&ev_vec);
        SDL_PumpEvents();
        SDL_RenderClear(igra.okno.renderer);
        img_vec.init(igra.okno.renderer, "common/images/vec.png", 0, 0, igra.okno.scalerCalculator(igra.okno.returnWindowWidth()), igra.okno.scalerCalculator(igra.okno.returnWindowHeight()));
        img_vec.display(igra.okno.renderer);
        if (igra.keys[SDL_SCANCODE_UP])
        {
            igra.sound.cursorMove();
            if (pozicija_cursorja == 1) {
                pozicija_cursorja = 4;
            }
            else {
                pozicija_cursorja--;
            }
        }
        else if (igra.keys[SDL_SCANCODE_DOWN])
        {
            igra.sound.cursorMove();
            if (pozicija_cursorja == 4) { pozicija_cursorja = 1; }
            else { pozicija_cursorja++; }
        }

        SDL_FreeSurface(igra.okno.image);

        switch (pozicija_cursorja)
        {
        case 1:
            cursor.init(igra.okno.renderer, "common/images/cursor.png", igra.okno.scalerCalculator(20), igra.okno.scalerCalculator(210), igra.okno.scalerCalculator(98), igra.okno.scalerCalculator(49));
            cursor.display(igra.okno.renderer);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.lestvica();

            }
            break;
        case 2:
            github.display(igra.okno.renderer);
            cursor.init(igra.okno.renderer, "common/images/cursor.png", igra.okno.scalerCalculator(20), igra.okno.scalerCalculator(310), igra.okno.scalerCalculator(98), igra.okno.scalerCalculator(49));
            cursor.display(igra.okno.renderer);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.izvorna();
                system("start https://github.com/urluur/ne_krznu");
            }
            break;
        case 3:
            cursor.init(igra.okno.renderer, "common/images/cursor.png", igra.okno.scalerCalculator(20), igra.okno.scalerCalculator(420), igra.okno.scalerCalculator(98), igra.okno.scalerCalculator(49));
            cursor.display(igra.okno.renderer);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.izbris();
            }

            break;
        case 4:
            cursor.init(igra.okno.renderer, "common/images/cursor.png", igra.okno.scalerCalculator(20), igra.okno.scalerCalculator(530), igra.okno.scalerCalculator(98), igra.okno.scalerCalculator(49));
            cursor.display(igra.okno.renderer);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.nazaj();
                main = 1;
            }
            break;
        }

        if (!(!igra.keys[SDL_SCANCODE_ESCAPE] || ev_vec.type != SDL_QUIT)) {
            main = 1;
        }

        SDL_RenderPresent(igra.okno.renderer);
        SDL_Delay(75);
    }

    //igra.sound.oof();
}

void animacija(GameManager& igra, int stAnim) {
    SDL_RenderClear(igra.okno.renderer);
    Image odzadje;
    switch (stAnim) {
    case 1:
        odzadje.init(igra.okno.renderer, "common/images/animacija1.png", 0, 0, igra.okno.scalerCalculator(igra.okno.returnWindowWidth()), igra.okno.scalerCalculator(igra.okno.returnWindowHeight()));
        odzadje.display(igra.okno.renderer);
        SDL_RenderPresent(igra.okno.renderer);
        break;
    case 2:
        odzadje.init(igra.okno.renderer, "common/images/animacija2.png", 0, 0, igra.okno.scalerCalculator(igra.okno.returnWindowWidth()), igra.okno.scalerCalculator(igra.okno.returnWindowHeight()));
        odzadje.display(igra.okno.renderer);
        SDL_RenderPresent(igra.okno.renderer);
        break;
    case 3:
        odzadje.init(igra.okno.renderer, "common/images/animacija3.png", 0, 0, igra.okno.scalerCalculator(igra.okno.returnWindowWidth()), igra.okno.scalerCalculator(igra.okno.returnWindowHeight()));
        odzadje.display(igra.okno.renderer);
        SDL_RenderPresent(igra.okno.renderer); break;
    case 4:
        odzadje.init(igra.okno.renderer, "common/images/animacija4.png", 0, 0, igra.okno.scalerCalculator(igra.okno.returnWindowWidth()), igra.okno.scalerCalculator(igra.okno.returnWindowHeight()));
        odzadje.display(igra.okno.renderer);
        SDL_RenderPresent(igra.okno.renderer);
        break;
    case 5:
        odzadje.init(igra.okno.renderer, "common/images/animacija5.png", 0, 0, igra.okno.scalerCalculator(igra.okno.returnWindowWidth()), igra.okno.scalerCalculator(igra.okno.returnWindowHeight()));
        odzadje.display(igra.okno.renderer);
        SDL_RenderPresent(igra.okno.renderer);
        break;
    default:
        cout << "Error: stAnim switch" << endl;
    }
    igra.sound.soundAnimacija(stAnim);
    SDL_Event ev_anim;
    SDL_Delay(500);
    SDL_PollEvent(&ev_anim);
    SDL_PumpEvents();
    Image img_press_enter;
    int blink = 0;
    img_press_enter.init(igra.okno.renderer, "common/images/pressreturn.png", 0, 0, igra.okno.scalerCalculator(igra.okno.returnWindowWidth()), igra.okno.scalerCalculator(igra.okno.returnWindowHeight()));
    while (!igra.keys[SDL_SCANCODE_RETURN]) {
        SDL_PollEvent(&ev_anim);
        SDL_PumpEvents();
        SDL_RenderClear(igra.okno.renderer);
        odzadje.display(igra.okno.renderer);
        if (blink < 100) {
            img_press_enter.display(igra.okno.renderer);
        }
        else if (blink > 150) {
            blink = 0;
        }
        blink++;
        SDL_RenderPresent(igra.okno.renderer);
        SDL_Delay(10);
    }
}

void premakniNaXY(GameManager &igra, int &x, int &y, int final_x, int final_y, Image &img_overworld, Image &img_player, int nivo){
    while (true) {
        if (x != final_x) {
            if (x < final_x) x++;
            else x--;
        }
        if (y != final_y) {
            if (y < final_y) y++;
            else y--;
        }
        if (x == final_x && y == final_y) break;

        SDL_RenderClear(igra.okno.renderer);
        img_overworld.display(igra.okno.renderer);
        img_player.init(igra.okno.renderer, "common/images/player.png", igra.okno.scalerCalculator(x), igra.okno.scalerCalculator(y), igra.okno.scalerCalculator(29), igra.okno.scalerCalculator(64));
        narisiFarmeAliDosezke(igra, nivo);
        img_player.display(igra.okno.renderer);
        SDL_RenderPresent(igra.okno.renderer);
        SDL_Delay(10);
    }
}

void haltEnter(GameManager& igra, Image& img_press_enter, SDL_Event &ev_overworld, int nivo) {
    SDL_PumpEvents();
    while (!igra.keys[SDL_SCANCODE_RETURN]) {
        SDL_PollEvent(&ev_overworld);
        SDL_PumpEvents();
        img_press_enter.display(igra.okno.renderer);
        SDL_RenderPresent(igra.okno.renderer);
    }
}

void narisiFarmeAliDosezke(GameManager& igra, int nivo) {
    Image monolith[5];
    int x[5] = {200, 100, 320, 460, 450};
    int y[5] = {160, 435, 420, 215, 95};
    switch (nivo) {
    case 0:
        monolith[0].init(igra.okno.renderer, "common/images/farma.png", igra.okno.scalerCalculator(x[0]), igra.okno.scalerCalculator(y[0]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        monolith[1].init(igra.okno.renderer, "common/images/farma.png", igra.okno.scalerCalculator(x[1]), igra.okno.scalerCalculator(y[1]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        monolith[2].init(igra.okno.renderer, "common/images/farma.png", igra.okno.scalerCalculator(x[2]), igra.okno.scalerCalculator(y[2]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        monolith[3].init(igra.okno.renderer, "common/images/farma.png", igra.okno.scalerCalculator(x[3]), igra.okno.scalerCalculator(y[3]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        monolith[4].init(igra.okno.renderer, "common/images/farma.png", igra.okno.scalerCalculator(x[4]), igra.okno.scalerCalculator(y[4]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        break;
    case 1:
        monolith[0].init(igra.okno.renderer, "common/images/iglu.png", igra.okno.scalerCalculator(x[0]), igra.okno.scalerCalculator(y[0]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        monolith[1].init(igra.okno.renderer, "common/images/farma.png", igra.okno.scalerCalculator(x[1]), igra.okno.scalerCalculator(y[1]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        monolith[2].init(igra.okno.renderer, "common/images/farma.png", igra.okno.scalerCalculator(x[2]), igra.okno.scalerCalculator(y[2]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        monolith[3].init(igra.okno.renderer, "common/images/farma.png", igra.okno.scalerCalculator(x[3]), igra.okno.scalerCalculator(y[3]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        monolith[4].init(igra.okno.renderer, "common/images/farma.png", igra.okno.scalerCalculator(x[4]), igra.okno.scalerCalculator(y[4]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        break;
    case 2:
        monolith[0].init(igra.okno.renderer, "common/images/iglu.png", igra.okno.scalerCalculator(x[0]), igra.okno.scalerCalculator(y[0]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        monolith[1].init(igra.okno.renderer, "common/images/iglu.png", igra.okno.scalerCalculator(x[1]), igra.okno.scalerCalculator(y[1]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        monolith[2].init(igra.okno.renderer, "common/images/farma.png", igra.okno.scalerCalculator(x[2]), igra.okno.scalerCalculator(y[2]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        monolith[3].init(igra.okno.renderer, "common/images/farma.png", igra.okno.scalerCalculator(x[3]), igra.okno.scalerCalculator(y[3]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        monolith[4].init(igra.okno.renderer, "common/images/farma.png", igra.okno.scalerCalculator(x[4]), igra.okno.scalerCalculator(y[4]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        break;
    case 3:
        monolith[0].init(igra.okno.renderer, "common/images/iglu.png", igra.okno.scalerCalculator(x[0]), igra.okno.scalerCalculator(y[0]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        monolith[1].init(igra.okno.renderer, "common/images/iglu.png", igra.okno.scalerCalculator(x[1]), igra.okno.scalerCalculator(y[1]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        monolith[2].init(igra.okno.renderer, "common/images/iglu.png", igra.okno.scalerCalculator(x[2]), igra.okno.scalerCalculator(y[2]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        monolith[3].init(igra.okno.renderer, "common/images/farma.png", igra.okno.scalerCalculator(x[3]), igra.okno.scalerCalculator(y[3]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        monolith[4].init(igra.okno.renderer, "common/images/farma.png", igra.okno.scalerCalculator(x[4]), igra.okno.scalerCalculator(y[4]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        break;
    case 4:
        monolith[0].init(igra.okno.renderer, "common/images/iglu.png", igra.okno.scalerCalculator(x[0]), igra.okno.scalerCalculator(y[0]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        monolith[1].init(igra.okno.renderer, "common/images/iglu.png", igra.okno.scalerCalculator(x[1]), igra.okno.scalerCalculator(y[1]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        monolith[2].init(igra.okno.renderer, "common/images/iglu.png", igra.okno.scalerCalculator(x[2]), igra.okno.scalerCalculator(y[2]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        monolith[3].init(igra.okno.renderer, "common/images/iglu.png", igra.okno.scalerCalculator(x[3]), igra.okno.scalerCalculator(y[3]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        monolith[4].init(igra.okno.renderer, "common/images/farma.png", igra.okno.scalerCalculator(x[4]), igra.okno.scalerCalculator(y[4]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        break;
    case 5:
        monolith[0].init(igra.okno.renderer, "common/images/iglu.png", igra.okno.scalerCalculator(x[0]), igra.okno.scalerCalculator(y[0]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        monolith[1].init(igra.okno.renderer, "common/images/iglu.png", igra.okno.scalerCalculator(x[1]), igra.okno.scalerCalculator(y[1]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        monolith[2].init(igra.okno.renderer, "common/images/iglu.png", igra.okno.scalerCalculator(x[2]), igra.okno.scalerCalculator(y[2]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        monolith[3].init(igra.okno.renderer, "common/images/iglu.png", igra.okno.scalerCalculator(x[3]), igra.okno.scalerCalculator(y[3]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        monolith[4].init(igra.okno.renderer, "common/images/iglu.png", igra.okno.scalerCalculator(x[4]), igra.okno.scalerCalculator(y[4]), igra.okno.scalerCalculator(66), igra.okno.scalerCalculator(61));
        break;
    default:
        cout << "Error: narisiFarmeAliDosezke switch" << endl;
    }

    for (int i = 0; i < 5; i++) {
        monolith[i].display(igra.okno.renderer);
    }
}
