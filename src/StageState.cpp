#include "StageState.h"

StageState::StageState() : backgroundMusic(BACKGROUND_MUSIC)
{
    // Create and initialize Background
    shared_ptr<GameObject> GOBg = shared_ptr<GameObject>(new GameObject());
    Sprite *newSprite = new Sprite(*GOBg, BACKGROUND_SPRITE);

    GOBg->box.x = 0;
    GOBg->box.y = 0;
    GOBg->box.w = newSprite->GetWidth();
    GOBg->box.h = newSprite->GetHeight();

    GOBg->AddComponent(newSprite);

    CameraFollower *follow = new CameraFollower(*GOBg);
    GOBg->AddComponent(follow);

    objectArray.emplace_back(move(GOBg));

    // Create and initialize TileMap
    shared_ptr<GameObject> GOMap = shared_ptr<GameObject>(new GameObject());

    GOMap->box.x = 0;
    GOMap->box.y = 0;

    TileSet *tSet = new TileSet(TILE_WIDTH, TILE_HEIGHT, TILE_SET_SOURCE);
    TileMap *tMap = new TileMap(*GOMap, TILE_MAP_SOURCE, tSet, PARALAX);

    GOMap->AddComponent(tMap);

    objectArray.emplace_back(move(GOMap));

    quitRequested = false;
    started = false;
    backgroundMusic.Play(-1);

    // Create and initialize Alien
    GameObject *alien_GO = new GameObject();
    weak_ptr<GameObject> weak_alien = AddObject(alien_GO);
    shared_ptr<GameObject> alien = weak_alien.lock();

    alien->box.x = 512;
    alien->box.y = 300;

    Alien *theAlien = new Alien(*alien, MINIONS);

    alien->AddComponent(theAlien);

    // Create and initialize Penguin
    GameObject *penguin_GO = new GameObject();
    weak_ptr<GameObject> weak_penguin = AddObject(penguin_GO);
    shared_ptr<GameObject> penguin = weak_penguin.lock();

    penguin->box.x = 704;
    penguin->box.y = 640;

    Camera::Follow(penguin.get());

    PenguinBody *thePenguin = new PenguinBody(*penguin);

    penguin->AddComponent(thePenguin);
}

StageState::~StageState()
{
    objectArray.clear();
}

void StageState::LoadAssets()
{
}

void StageState::Update(float dt)
{
    InputManager &IM = InputManager::GetInstance();
    Camera::Update(dt);

    if (IM.QuitRequested() || IM.KeyPress(ESCAPE_KEY))
        quitRequested = true;

    for (unsigned int i = 0; i < objectArray.size(); i++)
    {
        objectArray[i]->Update(dt);
        if (objectArray[i]->IsDead())
            objectArray.erase(objectArray.begin() + i);
    }

    for (unsigned int i = 0; i < objectArray.size(); i++)
    {
        Collider *firstCollider = dynamic_cast<Collider *>(objectArray[i]->GetComponent("Collider"));
        if (firstCollider != nullptr)
            for (unsigned int j = (i + 1); j < objectArray.size(); j++)
            {
                Collider *secondCollider = dynamic_cast<Collider *>(objectArray[j]->GetComponent("Collider"));
                if (secondCollider != nullptr && Collision::IsColliding(firstCollider->box, secondCollider->box, objectArray[i]->angleDeg * (PI / 180), objectArray[i]->angleDeg * (PI / 180)))
                {
                    objectArray[i]->NotifyCollision(*(objectArray[j]));
                    objectArray[j]->NotifyCollision(*(objectArray[i]));
                }
            }
    }

    SDL_Delay(dt);
}

void StageState::Render()
{
    TileMap *tmap;

    for (unsigned int i = 0; i < objectArray.size(); i++)
    {
        objectArray[i]->Render();
        if (objectArray[i]->GetComponent("TileMap") != nullptr)
            tmap = static_cast<TileMap *>(objectArray[i]->GetComponent("TileMap"));
    }

    if (tmap != nullptr)
        for (int i = 1; i < tmap->GetDepth(); i++)
            tmap->RenderLayer(i, Camera::pos.x * (1 + i * PARALAX), Camera::pos.y * (1 + i * PARALAX));
}

void StageState::Start()
{
    LoadAssets();

    StartArray();

    started = true;
}

void StageState::Pause()
{
}

void StageState::Resume()
{
}