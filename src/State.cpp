#include <State.h>

std::vector<std::unique_ptr<GameObject>>::iterator it;

State::State() : music(BACKGROUND_MUSIC)
{
    // Create and initialize Background
    bg = shared_ptr<GameObject>(new GameObject());
    Sprite *newSprite = new Sprite(*bg, BACKGROUND_SPRITE);

    bg->box.x = 0;
    bg->box.y = 0;
    bg->box.w = newSprite->GetWidth();
    bg->box.h = newSprite->GetHeight();

    bg->AddComponent(newSprite);

    CameraFollower *follow = new CameraFollower(*bg);
    bg->AddComponent(follow);

    objectArray.emplace_back(move(bg));

    // Create and initialize TileMap
    shared_ptr<GameObject> GOMap = shared_ptr<GameObject>(new GameObject());

    GOMap->box.x = 0;
    GOMap->box.y = 0;

    TileSet *tSet = new TileSet(TILE_WIDTH, TILE_HEIGHT, TILE_SET_SOURCE);
    TileMap *tMap = new TileMap(*GOMap, TILE_MAP_SOURCE, tSet, 2);

    GOMap->AddComponent(tMap);

    objectArray.emplace_back(move(GOMap));

    quitRequested = false;
    started = false;
    music.Play(-1);

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

State::~State()
{
    objectArray.clear();
}

bool State::QuitRequested()
{
    return quitRequested;
}

void State::LoadAssets()
{
}

void State::Update(float dt)
{
    InputManager &IM = InputManager::GetInstance();
    Camera::Update(dt);

    if (IM.QuitRequested() || IM.KeyPress(ESCAPE_KEY))
        quitRequested = true;

    if (IM.KeyPress(SPACE_KEY))
    {
        Vec2 pos = Vec2(200, 0).GetRotated(-PI + PI * (rand() % 1001) / 500.0) + Vec2(IM.GetMouseX(), IM.GetMouseY());
        // AddObject((int)objPos.x, (int)objPos.y);
        //cout << "X = " << (int)objPos.x << " Y = " << (int)objPos.y << endl;
    }

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
    //quitRequested = (SDL_QuitRequested() == true) ? true : false;

    SDL_Delay(dt);
}

void State::Render()
{

    for (unsigned int i = 0; i < objectArray.size(); i++)
        objectArray[i]->Render();
}

weak_ptr<GameObject> State::AddObject(GameObject *go)
{
    shared_ptr<GameObject> shared = make_shared<GameObject>(*go);

    objectArray.push_back(shared);
    if (started)
        objectArray.back()->Start();

    return weak_ptr<GameObject>(objectArray.back());
}

void State::Start()
{
    LoadAssets();
    for (unsigned int i = 0; i < objectArray.size(); i++)
    {
        objectArray[i]->Start();
    }
    started = true;
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject *go)
{
    for (unsigned int i = 0; i < objectArray.size(); i++)
    {
        if (objectArray[i].get() == go)
            return (weak_ptr<GameObject>)objectArray[i];
    }
    return weak_ptr<GameObject>();
}