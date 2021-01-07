#pragma once
using namespace std;

class Sounds {
private:
    Mix_Music* bgm;
    int mute;
    bool played;
public:
    Sounds();
    void toggle();
    void oof();
    void cursorMove();
    ~Sounds(){
        bgm = nullptr;
        Mix_Quit();
    }
};

Sounds::Sounds(){
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
    if(mute == 0)
        played = PlaySound(TEXT("common/sounds/cur_mov.wav"), NULL, SND_ASYNC);
}
void Sounds::oof() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/oof.wav"), NULL, SND_SYNC);
}