#include "sounds.h"
using namespace std;
Sounds::Sounds() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "Mixer error: " << Mix_GetError() << endl;
    }
    bgm = Mix_LoadMUS("common/sounds/soundtrack.wav");
    if (!Mix_PlayingMusic()) {
        Mix_PlayMusic(bgm, -1);
    }
    mute = 0;
}

void Sounds::toggle() {
    if (mute == 0) {
        mute = 1;
        Mix_PauseMusic();
        cout << "Glasba se je ustavila .." << endl;
    }
    else {
        mute = 0;
        Mix_ResumeMusic();
        cout << "Glasba se nadaljuje.." << endl;
    }

}
void Sounds::cursorMove() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/cur_mov.wav"), NULL, SND_ASYNC);
}
void Sounds::oof() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/oof.wav"), NULL, SND_SYNC);
}
void Sounds::dimenzije(){
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/dimenzije.wav"), NULL, SND_ASYNC);
}
void Sounds::izhod() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/izhod.wav"), NULL, SND_SYNC);
}
void Sounds::nastavitve() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/nastavitve.wav"), NULL, SND_SYNC);
}
void Sounds::nasvidenje() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/nasvidenje.wav"), NULL, SND_SYNC);
}
void Sounds::nazaj() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/nazaj.wav"), NULL, SND_SYNC);
}
void Sounds::spremeni_ime() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/spremeni_ime.wav"), NULL, SND_ASYNC);
}
void Sounds::spremeni_zvok() {
    played = PlaySound(TEXT("common/sounds/spremeni_zvok.wav"), NULL, SND_ASYNC);
}
void Sounds::vec() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/vec.wav"), NULL, SND_ASYNC);
}
void Sounds::zacni() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/zacni.wav"), NULL, SND_ASYNC);
}

Sounds::~Sounds() {
    bgm = nullptr;
    Mix_Quit();
}