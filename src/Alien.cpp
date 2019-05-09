#include "Alien.h"

#define ALIEN_SOURCE "assets/img/alien.png"
#define DISTANCE_ERROR 1

Alien::Alien(GameObject &associated, int nMinions) : Component(associated)
{
    Sprite *alien = new Sprite(associated, ALIEN_SOURCE);

    associated.AddComponent(alien);

    hp = ALIEN_HP;
    speed.x = 0;
    speed.y = 0;
}

Alien::~Alien()
{
}

void Alien::Start()
{
    // Retornar aqui
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
        Action *action = new Action(Action::MOVE, (float)input.GetMouseX() - Camera::pos.x + associated.box.w, (float)input.GetMouseY() - Camera::pos.y + associated.box.h);
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

            if ((associated.box.x + associated.box.w / 2 < taskQueue.front().pos.x + DISTANCE_ERROR) && (associated.box.x > taskQueue.front().pos.x - DISTANCE_ERROR) && (associated.box.y < taskQueue.front().pos.y + DISTANCE_ERROR) && (associated.box.y > taskQueue.front().pos.y - DISTANCE_ERROR))
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