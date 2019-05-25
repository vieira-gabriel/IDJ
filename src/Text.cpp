#include "Text.h"

Text::Text(GameObject &associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color) : Component(associated)
{
    texture = nullptr;
    this->fontFile = fontFile;
    this->fontSize = fontSize;
    this->style = style;
    this->text = text;
    this->color = color;

    RemakeTexture();
}

Text::~Text()
{
    if (texture != nullptr)
        SDL_DestroyTexture(texture);
}

void Text::Update(float dt)
{
    timer.Update(dt);
}

void Text::Render()
{
    Game &instance = Game::GetInstance();

    if (timer.Get() > TIMER)
    {
        SDL_Rect clipRect = {0, 0, (int)associated.box.w, (int)associated.box.h};

        SDL_Rect dstRect;
        dstRect.x = associated.box.x - Camera::pos.x;
        dstRect.y = associated.box.y - Camera::pos.y;
        dstRect.w = clipRect.w;
        dstRect.h = clipRect.h;

        if (SDL_RenderCopyEx(instance.GetRenderer(), texture, &clipRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE) != 0)
        {
            std::cout << "Fail to render the texture: " << SDL_GetError() << std::endl;
            exit(1);
        }
        if (timer.Get() > 2 * TIMER)
            timer.Restart();
    }
}

bool Text::Is(string type)
{
    // Return true if the type wanted is Text
    return (type == "Text");
}

void Text::SetText(string text)
{
    this->text = text;
}

void Text::SetColor(SDL_Color color)
{
    this->color = color;
}

void Text::SetStyle(TextStyle style)
{
    this->style = style;
}

void Text::SetFontFile(string fontFile)
{
    this->fontFile = fontFile;
}

void Text::SetFontSize(int fontSize)
{
    this->fontSize = fontSize;
}

void Text::RemakeTexture()
{
    Game &instance = Game::GetInstance();

    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    font = Resources::GetFont(fontFile, fontSize);
    if (font == nullptr)
    {
        cout << "Fale to load font: " << fontFile.c_str() << endl;
        cout << "SDL_GetError: " << SDL_GetError() << endl;
        exit(1);
    }

    SDL_Surface *type;

    if (style == SOLID)
        type = TTF_RenderText_Solid(font.get(), text.c_str(), color);

    else if (style == SHADED)
        type = TTF_RenderText_Shaded(font.get(), text.c_str(), color, {0, 0, 0, 255});

    else if (style == BLENDED)
        type = TTF_RenderText_Blended(font.get(), text.c_str(), color);

    else
    {
        cout << "Error: not defined style" << endl;
        return;
    }

    associated.box.w = type->w;
    associated.box.h = type->h;

    texture = SDL_CreateTextureFromSurface(instance.GetRenderer(), type);
    SDL_FreeSurface(type);
}