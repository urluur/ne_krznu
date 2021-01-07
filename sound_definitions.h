#pragma once
void sound_cursorMove() {
    bool played = PlaySound(TEXT("common/sounds/cur_mov.wav"), NULL, SND_ASYNC);
}
void sound_oof() {
    bool played = PlaySound(TEXT("common/sounds/oof.wav"), NULL, SND_SYNC);
}