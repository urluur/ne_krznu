#pragma once
#include <windows.h>
#include <iostream>
#include <MMSystem.h>
#include <SDL_mixer.h>
class SoundManager
{
private:
	Mix_Music* bgm;
    int mute;
    bool played;
public:
	SoundManager();
    void toggle();
    void oof();
    void cursorMove();
    void dimenzije();
    void izhod();
    void nastavitve();
    void nasvidenje();
    void nazaj();
    void spremeni_ime();
    void spremeni_zvok();
    void vec();
    void zacni();
    void lestvica();
    void izvorna();
    void izbris();
    void animacija1();
    void animacija2();
    void animacija3();
    void animacija4();
    void animacija5();
    ~SoundManager();
};

