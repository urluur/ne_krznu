#pragma once
void sound_cursorMove() {
    bool played = PlaySound(TEXT("cur_mov.wav"), NULL, SND_ASYNC);
}