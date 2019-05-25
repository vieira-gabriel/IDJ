#pragma once

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include <SDL_include.h>
#include "Component.h"
#include "Game.h"
#include "Camera.h"
#include "Resources.h"
#include "Timer.h"

#define TIMER 0.5

class Text : public Component
{
public:
    enum TextStyle
    {
        SOLID,
        SHADED,
        BLENDED
    };

    Text(GameObject &associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color);
    ~Text();

    void Update(float dt);
    void Render();
    bool Is(string type);

    void SetText(string text);
    void SetColor(SDL_Color color);
    void SetStyle(TextStyle style);
    void SetFontFile(string fontFile);
    void SetFontSize(int fontSize);

private:
    shared_ptr<TTF_Font> font;
    SDL_Texture *texture;

    string text;
    TextStyle style;
    string fontFile;
    int fontSize;
    SDL_Color color;
    Timer timer;

    void RemakeTexture();
};
