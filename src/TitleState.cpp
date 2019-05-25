#include "TitleState.h"

TitleState::TitleState()
{
}

TitleState::~TitleState()
{
    objectArray.clear();
}

void TitleState::LoadAssets()
{
    shared_ptr<GameObject> GOSprite = shared_ptr<GameObject>(new GameObject());
    Sprite *titleSprite = new Sprite(*GOSprite, TITLE_SPRITE);

    GOSprite->box.x = 0;
    GOSprite->box.y = 0;
    GOSprite->box.w = titleSprite->GetWidth();
    GOSprite->box.h = titleSprite->GetHeight();

    shared_ptr<GameObject> GOTitle = shared_ptr<GameObject>(new GameObject());
    Text *text = new Text(*GOTitle.get(), TITLE_SOURCE, 50, Text::TextStyle::BLENDED, TITLE_TEXT, {190, 50, 50, 255});

    GOTitle->box.SetCenter({514, 500});
    GOSprite->box.w = titleSprite->GetWidth();
    GOSprite->box.h = titleSprite->GetHeight();

    GOSprite->AddComponent(titleSprite);
    GOTitle->AddComponent(text);
    objectArray.emplace_back(move(GOSprite));
    objectArray.emplace_back(move(GOTitle));
}

void TitleState::Update(float dt)
{
    InputManager &input = InputManager::GetInstance();

    // Close
    if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY))
    {
        quitRequested = true;
    }

    // Initialize
    if (input.KeyPress(SPACE_KEY))
    {
        StageState *stage = new StageState();
        Game::GetInstance().Push(stage);
    }

    UpdateArray(dt);
}

void TitleState::Render()
{
    RenderArray();
}

void TitleState::Start()
{
    LoadAssets();

    StartArray();

    started = true;
}

void TitleState::Pause()
{
}

void TitleState::Resume()
{
    Camera::pos.x = 0;
    Camera::pos.y = 0;
}
