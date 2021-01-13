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
     
    int x, y;
    int final_x, final_y;
    bool x_bool=false, y_bool=false;

    while (main == 0) {
        SDL_Delay(500);
        SDL_PollEvent(&ev_overworld);
        SDL_PumpEvents();
        SDL_RenderClear(igra.okno.renderer);
        img_overworld.init(igra.okno.renderer, "common/images/overworld.png", 0, 0, igra.okno.scalerCalculator(igra.okno.returnWindowWidth()), igra.okno.scalerCalculator(igra.okno.returnWindowHeight()));
        img_overworld.display(igra.okno.renderer);
        SDL_RenderPresent(igra.okno.renderer);

        switch (level_clear) {
        case 0:
            img_player.init(igra.okno.renderer, "common/images/player.png", igra.okno.scalerCalculator(55), igra.okno.scalerCalculator(160), igra.okno.scalerCalculator(29), igra.okno.scalerCalculator(64));
            img_player.display(igra.okno.renderer);
            img_press_enter.init(igra.okno.renderer, "common/images/pressreturn.png", 0, 0, igra.okno.scalerCalculator(igra.okno.returnWindowWidth()), igra.okno.scalerCalculator(igra.okno.returnWindowHeight()));
            while (!igra.keys[SDL_SCANCODE_RETURN]) {
                SDL_PollEvent(&ev_overworld);
                SDL_PumpEvents();
                img_press_enter.display(igra.okno.renderer);
                SDL_RenderPresent(igra.okno.renderer);
            }
            animacija1(igra);
            cout << "Prvi nivo" << endl;
            //level_clear = level1();
            level_clear = 1;
            break;
        case 1:
            img_press_enter.init(igra.okno.renderer, "common/images/pressreturn.png", 0, 0, igra.okno.scalerCalculator(igra.okno.returnWindowWidth()), igra.okno.scalerCalculator(igra.okno.returnWindowHeight()));
            for (int i = 55; i < 180; i++) { //na 180, 160
                SDL_RenderClear(igra.okno.renderer);
                img_overworld.display(igra.okno.renderer);
                img_player.init(igra.okno.renderer, "common/images/player.png", igra.okno.scalerCalculator(i), igra.okno.scalerCalculator(160), igra.okno.scalerCalculator(29), igra.okno.scalerCalculator(64));
                img_player.display(igra.okno.renderer);
                SDL_RenderPresent(igra.okno.renderer);
                SDL_Delay(10);
            }
            
            SDL_PumpEvents();
            while (!igra.keys[SDL_SCANCODE_RETURN]) {
                SDL_PollEvent(&ev_overworld);
                SDL_PumpEvents();
                img_press_enter.display(igra.okno.renderer);
                SDL_RenderPresent(igra.okno.renderer);
            }
            //animacija2(igra);
            cout << "Drugi nivo" << endl;
            //level_clear = level2();
            level_clear = 2;
            break;
        case 2:
            x = 180;
            y = 160;
            img_press_enter.init(igra.okno.renderer, "common/images/pressreturn.png", 0, 0, igra.okno.scalerCalculator(igra.okno.returnWindowWidth()), igra.okno.scalerCalculator(igra.okno.returnWindowHeight()));
            while (x>90 && y<300) {
                x--;
                y++;
                SDL_RenderClear(igra.okno.renderer);
                img_overworld.display(igra.okno.renderer);
                img_player.init(igra.okno.renderer, "common/images/player.png", igra.okno.scalerCalculator(x), igra.okno.scalerCalculator(y), igra.okno.scalerCalculator(29), igra.okno.scalerCalculator(64));
                img_player.display(igra.okno.renderer);
                SDL_RenderPresent(igra.okno.renderer);
                SDL_Delay(10);
            }
            final_x = 165;
            final_y = 350;
            while (true) {
                if (x != final_x) {
                    if (x < final_x) {
                        x++;
                    }
                    else {
                        x--;
                    }
                }
                if (y != final_y) {
                    if (y < final_y) {
                        y++;
                    }
                    else {
                        y--;
                    }
                }
                if (x == final_x && y == final_y) {
                    break;
                }
                SDL_RenderClear(igra.okno.renderer);
                img_overworld.display(igra.okno.renderer);
                img_player.init(igra.okno.renderer, "common/images/player.png", igra.okno.scalerCalculator(x), igra.okno.scalerCalculator(y), igra.okno.scalerCalculator(29), igra.okno.scalerCalculator(64));
                img_player.display(igra.okno.renderer);
                SDL_RenderPresent(igra.okno.renderer);
                SDL_Delay(10);
            }

            SDL_PumpEvents();
            while (!igra.keys[SDL_SCANCODE_RETURN]) {
                SDL_PollEvent(&ev_overworld);
                SDL_PumpEvents();
                img_press_enter.display(igra.okno.renderer);
                SDL_RenderPresent(igra.okno.renderer);
            }
            //animacija3(igra);
            cout << "Tretji nivo" << endl;
            //level_clear = level3();
            level_clear = 3;
            break;
        case 3:
            level_clear = 4;
            //animacija4(igra);
            cout << "Cetrti nivo" << endl;
            SDL_Delay(1000);
            break;
        case 4:
            level_clear = 5;
            //animacija5(igra);
            cout << "Peti nivo" << endl;
            SDL_Delay(1000);
            break;
        case 5:
            cout << "Zmaga!" << endl;
            img_zastavica_fullscreen.init(igra.okno.renderer, "common/images/zastavica_fullscreen.png", 0, 0, igra.okno.scalerCalculator(igra.okno.returnWindowWidth()), igra.okno.scalerCalculator(igra.okno.returnWindowHeight()));
            img_zastavica_fullscreen.display(igra.okno.renderer);
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

void animacija1(GameManager& igra) {
    //clear
    SDL_RenderClear(igra.okno.renderer);
    Image odzadje;
    odzadje.init(igra.okno.renderer, "common/images/animacija1.png", 0, 0, igra.okno.scalerCalculator(igra.okno.returnWindowWidth()), igra.okno.scalerCalculator(igra.okno.returnWindowHeight()));
    odzadje.display(igra.okno.renderer);

    //refresh
    SDL_RenderPresent(igra.okno.renderer);
    igra.sound.animacija1();
    SDL_Event ev_anim1;
    SDL_Delay(500);
    SDL_PollEvent(&ev_anim1);
    SDL_PumpEvents();
    Image img_press_enter;
    int blink = 0;
    img_press_enter.init(igra.okno.renderer, "common/images/pressreturn.png", 0, 0, igra.okno.scalerCalculator(igra.okno.returnWindowWidth()), igra.okno.scalerCalculator(igra.okno.returnWindowHeight()));
    while (!igra.keys[SDL_SCANCODE_RETURN]) {
        SDL_PollEvent(&ev_anim1);
        SDL_PumpEvents();
        SDL_RenderClear(igra.okno.renderer);
        odzadje.display(igra.okno.renderer);
        if (blink < 100) {
            img_press_enter.display(igra.okno.renderer);
        }
        else if(blink > 150){
            blink = 0;
        }
        blink++;
        SDL_RenderPresent(igra.okno.renderer);
        SDL_Delay(10);
    }
}