#include "TitleState.h"

TitleState::TitleState()
{
    shared_ptr<GameObject> GOTitle = shared_ptr<GameObject>(new GameObject());
    Sprite *titleSprite = new Sprite(*GOTitle, TITLE_SPRITE);

    GOTitle->box.x = 0;
    GOTitle->box.y = 0;
    GOTitle->box.w = titleSprite->GetWidth();
    GOTitle->box.h = titleSprite->GetHeight();

    GOTitle->AddComponent(titleSprite);
    objectArray.emplace_back(move(GOTitle));
}

TitleState::~TitleState()
{
    objectArray.clear();
}

void TitleState::LoadAssets()
{
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
