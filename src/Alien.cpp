#include "Alien.h"

#define ALIEN_SOURCE "assets/img/alien.png"
#define DISTANCE_ERROR 2

Alien::Alien(GameObject &associated, int nMinions) : Component(associated)
{
    Sprite *alien = new Sprite(associated, ALIEN_SOURCE);

    associated.AddComponent(alien);

    associated.box.x -= associated.box.w / 2;
    associated.box.y -= associated.box.h / 2; // Centralizare Alien

    hp = ALIEN_HP;
    speed.x = 0;
    speed.y = 0;
    this->nMinions = nMinions;
}

Alien::~Alien()
{
    minionArray.clear();
}

void Alien::Start()
{
    for (int i = 0; i < nMinions; i++)
    {
        GameObject *minion_GO(new GameObject());

        weak_ptr<GameObject> weak_Alien = Game::GetInstance().GetState().GetObjectPtr(&associated);

        Minion *minion = new Minion(*minion_GO, weak_Alien, (360.0 / nMinions) * i);

        minion_GO->AddComponent(minion);

        std::weak_ptr<GameObject> weak_minion = Game::GetInstance().GetState().AddObject(minion_GO);
        minionArray.emplace_back(weak_minion);
    }
}

void Alien::Update(float dt)
{
    InputManager &input = InputManager::GetInstance();

    if (input.MousePress(LEFT_MOUSE_BUTTON))
    {
        Action *action = new Action(Action::SHOOT, (float)input.GetMouseX() + Camera::pos.x, (float)input.GetMouseY() + Camera::pos.y);
        taskQueue.emplace(*action);
    }
    else if (input.MousePress(RIGHT_MOUSE_BUTTON))
    {
        Action *action = new Action(Action::MOVE, (float)input.GetMouseX() - Camera::pos.x - associated.box.w / 2, (float)input.GetMouseY() - Camera::pos.y - associated.box.h / 2);
        taskQueue.emplace(*action);
    }

    if (!taskQueue.empty())
    {
        if (taskQueue.front().type == Action::MOVE)
        {
            Vec2 vector;
            vector.x = taskQueue.front().pos.x - associated.box.x;
            vector.y = taskQueue.front().pos.y - associated.box.y;
            float mag = vector.Mag();
            speed.x = (vector.x / mag) * ALIEN_SPEED;
            speed.y = (vector.y / mag) * ALIEN_SPEED;

            if ((vector.x > -(dt * abs(speed.x))) && (vector.x < (dt * abs(speed.x))) && (vector.y > -(dt * abs(speed.y))) && (vector.y < (dt * abs(speed.y))))
            {
                speed.x = 0;
                speed.y = 0;
                taskQueue.pop();
            }

            associated.box.x += speed.x * dt;
            associated.box.y += speed.y * dt;
        }
        else if (taskQueue.front().type == Action::SHOOT)
        {
            taskQueue.pop();
        }
    }
    if (hp <= 0)
    {
        associated.RequestDelete();
    }
}

void Alien::Render()
{
}

bool Alien::Is(string type)
{
    return (type == "Alien");
}

Alien::Action::Action(ActionType type, float x, float y)
{
    this->type = type;
    this->pos.x = x;
    this->pos.y = y;
}