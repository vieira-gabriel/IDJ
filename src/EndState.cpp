#include "EndState.h"

EndState::EndState()
{
    GameObject *GOEnd = new GameObject();

    weak_ptr<GameObject> weakEnd = AddObject(GOEnd);
    shared_ptr<GameObject> sharedEnd = weakEnd.lock();
    CameraFollower *follow = new CameraFollower(*sharedEnd);

    sharedEnd->box.x = 0;
    sharedEnd->box.y = 0;

    GameObject *GOText = new GameObject();

    weak_ptr<GameObject> weakText = AddObject(GOText);
    shared_ptr<GameObject> sharedText = weakText.lock();

    Text *tx1 = new Text(*sharedText, TEXT_TYPE, 50, Text::BLENDED, "Press Space To Play Again", {50, 70, 255, 255});
    sharedText->box.SetCenter({512, 300});

    GameObject *GOText2 = new GameObject();

    weak_ptr<GameObject> weakText2 = AddObject(GOText2);
    shared_ptr<GameObject> sharedText2 = weakText2.lock();

    Text *tx2 = new Text(*sharedText2, TEXT_TYPE, 50, Text::BLENDED, "Press ESC To Exit", {50, 70, 255, 255});
    sharedText2->box.SetCenter({512, 400});

    if (GameData::playerVictory)
    {
        Sprite *winSprite = new Sprite(*sharedEnd, WIN_SOURCE);
        sharedEnd->AddComponent(winSprite);

        backgroundMusic.Open(WIN_MUSIC);
    }
    else
    {
        Sprite *loseSprite = new Sprite(*sharedEnd, LOSE_SOURCE);
        sharedEnd->AddComponent(loseSprite);

        backgroundMusic.Open(LOSE_MUSIC);
    }

    sharedText->AddComponent(tx1);
    sharedText2->AddComponent(tx2);
    sharedEnd->AddComponent(follow);
}

EndState::~EndState()
{
    objectArray.clear();
}

void EndState::LoadAssets()
{
}

void EndState::Update(float dt)
{
    InputManager &IM = InputManager::GetInstance();

    // Close
    if (IM.QuitRequested() || IM.KeyPress(ESCAPE_KEY))
    {
        quitRequested = true;
    }

    // Initialize
    if (IM.KeyPress(SPACE_KEY))
    {
        TitleState *title = new TitleState();
        popRequested = true;
        Game::GetInstance().Push(title);
    }

    UpdateArray(dt);
}

void EndState::Render()
{
    RenderArray();
}

void EndState::Start()
{
    LoadAssets();

    StartArray();

    backgroundMusic.Play(-1);

    started = true;
}

void EndState::Pause()
{
}

void EndState::Resume()
{
    Camera::pos.x = 0;
    Camera::pos.y = 0;
}
