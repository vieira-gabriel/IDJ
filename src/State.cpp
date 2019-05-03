#include <State.h>

#define BACKGROUND_SPRITE "assets/img/ocean.jpg"
#define BACKGROUND_MUSIC "assets/audio/stageState.ogg"
#define PENGUIN_SOURCE "assets/img/penguinface.png"
#define PENGUIN_SOUND "assets/audio/boom.wav"
#define TILE_MAP_SOURCE "assets/map/tileMap.txt"
#define TILE_SET_SOURCE "assets/img/tileset.png"
#define TILE_WIDTH 64
#define TILE_HEIGHT 64
#define PI 3.14159265

std::vector<std::unique_ptr<GameObject>>::iterator it;

State::State() : music(BACKGROUND_MUSIC)
{
    // Create and initialize Background
    bg = shared_ptr<GameObject>(new GameObject());
    Sprite *newSprite = new Sprite(*bg, BACKGROUND_SPRITE);
    CameraFollower *follow = new CameraFollower(*bg);

    bg->box.x = 0;
    bg->box.y = 0;
    bg->box.w = newSprite->GetWidth();
    bg->box.h = newSprite->GetHeight();

    bg->AddComponent(newSprite);
    bg->AddComponent(follow);

    objectArray.emplace_back(std::move(bg));

    // Crate and initialize TileMap
    shared_ptr<GameObject> GOMap = shared_ptr<GameObject>(new GameObject());

    GOMap->box.x = 0;
    GOMap->box.y = 0;

    TileSet *tSet = new TileSet(TILE_WIDTH, TILE_HEIGHT, TILE_SET_SOURCE);
    TileMap *tMap = new TileMap(*GOMap, TILE_MAP_SOURCE, tSet, 0);

    GOMap->AddComponent(tMap);

    objectArray.emplace_back(std::move(GOMap));

    quitRequested = false;
    music.Play(-1);
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
        Vec2 objPos = Vec2(200, 0).GetRotated(-PI + PI * (rand() % 1001) / 500.0) + Vec2(IM.GetMourseX(), IM.GetMourseY());
        AddObject((int)objPos.x, (int)objPos.y);
        //cout << "X = " << (int)objPos.x << " Y = " << (int)objPos.y << endl;
    }

    for (auto i = 0; i < objectArray.size(); i++)
    {
        objectArray[i]->Update(dt);
        if (objectArray[i]->IsDead())
            objectArray.erase(objectArray.begin() + i);
    }
    //quitRequested = (SDL_QuitRequested() == true) ? true : false;

    SDL_Delay(dt);
}

void State::Render()
{

    for (auto i = 0; i < objectArray.size(); i++)
        objectArray[i]->Render();
}

void State::Input()
{
    SDL_Event event;
    int mouseX, mouseY;

    // Obtenha as coordenadas do mouse
    SDL_GetMouseState(&mouseX, &mouseY);

    // SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
    while (SDL_PollEvent(&event))
    {

        // Se o evento for quit, setar a flag para terminação
        if (event.type == SDL_QUIT)
        {
            quitRequested = true;
        }

        // Se o evento for clique...
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {

            // Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
            for (int i = objectArray.size() - 1; i >= 0; --i)
            {
                // Obtem o ponteiro e casta pra Face.
                GameObject *go = (GameObject *)objectArray[i].get();
                // Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
                // O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
                // ao usar get(), violamos esse princípio e estamos menos seguros.
                // Esse código, assim como a classe Face, é provisório. Futuramente, para
                // chamar funções de GameObjects, use objectArray[i]->função() direto.

                if (go->box.Contains((float)mouseX, (float)mouseY))
                {
                    Face *face = (Face *)go->GetComponent("Face");
                    if (nullptr != face)
                    {
                        // Aplica dano
                        face->Damage(std::rand() % 10 + 10);
                        // Sai do loop (só queremos acertar um)
                        break;
                    }
                }
            }
        }
        if (event.type == SDL_KEYDOWN)
        {
            // Se a tecla for ESC, setar a flag de quit
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                quitRequested = true;
            }
            // Se não, crie um objeto
            else
            {
                Vec2 objPos = Vec2(200, 0).GetRotated(-PI + PI * (rand() % 1001) / 500.0) + Vec2(mouseX, mouseY);
                AddObject((int)objPos.x, (int)objPos.y);
            }
        }
    }
}

void State::AddObject(int mouseX, int mouseY)
{
    GameObject *enemy = new GameObject();

    Sprite *theEnemy = new Sprite(*enemy, PENGUIN_SOURCE);
    Face *enemyFace = new Face(*enemy);
    Sound *enemySound = new Sound(*enemy, PENGUIN_SOUND);

    enemy->box.x = mouseX - Camera::pos.x;
    enemy->box.y = mouseY - Camera::pos.y;
    enemy->box.w = theEnemy->GetWidth();
    enemy->box.h = theEnemy->GetHeight();
    //compensar o tamanho da sprite

    enemy->AddComponent(enemySound);

    enemy->AddComponent(theEnemy);

    enemy->AddComponent(enemyFace);

    objectArray.emplace_back(std::move(enemy));
}