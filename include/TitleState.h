#pragma once

#include "StageState.h"
#include "Text.h"

const string TITLE_SPRITE = "assets/img/title.jpg";
const string TITLE_SOURCE = "assets/font/Call me maybe.ttf";
const string TITLE_TEXT = "Press space to start";
class Text;

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