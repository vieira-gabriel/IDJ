#pragma once

#include "State.h"
#include "Music.h"
#include "GameData.h"
#include "StageState.h"
#include "Text.h"
#include "TitleState.h"

const string WIN_SOURCE = "assets/img/win.jpg";
const string LOSE_SOURCE = "assets/img/lose.jpg";
const string TEXT_TYPE = "assets/font/Call me maybe.ttf";
const string WIN_MUSIC = "assets/audio/endStateWin.ogg";
const string LOSE_MUSIC = "assets/audio/endStateLose.ogg";

class EndState : public State
{
private:
    Music backgroundMusic;

public:
    EndState();
    ~EndState();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
};