#pragma once

#include "StageState.h"

#define TITLE_SPRITE "assets/img/title.png"

class TitleState : public State
{
public:
    TitleState();
    ~TitleState();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
};