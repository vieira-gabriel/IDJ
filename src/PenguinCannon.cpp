#include "PenguinCannon.h"

PenguinCannon::PenguinCannon(GameObject &associated, weak_ptr<GameObject> penguinBody) : Component(associated)
{
    Sprite *cannon = new Sprite(associated, CANNON_SOURCE);
    Collider *coliderBox = new Collider(associated);

    associated.AddComponent(cannon);
    associated.AddComponent(coliderBox);

    pbody = penguinBody;
    angle = 0;
}

PenguinCannon::~PenguinCannon()
{
}

void PenguinCannon::Update(float dt)
{
    shared_ptr<GameObject> pbody_shared = pbody.lock();
    InputManager &input = InputManager::GetInstance();
    static Timer time;

    if (pbody_shared == nullptr)
    {
        associated.RequestDelete();
        return;
    }

    associated.box.x = pbody_shared->box.x - pbody_shared->box.w + associated.box.w;
    associated.box.y = pbody_shared->box.y - pbody_shared->box.h + associated.box.h;

    Vec2 direction = Vec2(input.GetMouseX() + Camera::pos.x, input.GetMouseY() + Camera::pos.y);
    direction -= associated.box.CenterPoint();
    angle = direction.Inclination();
    associated.angleDeg = angle;

    time.Update(dt);
    if (input.MousePress(LEFT_MOUSE_BUTTON))
    {
        if (time.Get() > COOLDOWN)
        {
            Shoot();
            time.Restart();
        }
    }
}
void PenguinCannon::Render()
{
}
bool PenguinCannon::Is(string type)
{
    return (type == "PenguinCannon");
}
void PenguinCannon::Shoot()
{
    GameObject *bullet_GO = new GameObject;
    weak_ptr<GameObject> weak_bullet = Game::GetInstance().GetState().AddObject(bullet_GO);
    shared_ptr<GameObject> shared_bullet = weak_bullet.lock();

    Bullet *bullet = new Bullet(*shared_bullet, angle, PENGUIN_BULLET_SPEED, PENGUIN_BULLET_DAMAGE, PENGUIN_BULLET_DISTANCE, PENGUIN_BULLET_SOURCE, P_BULLET_FRAMES, P_BULLET_FM_TIME, false);

    shared_bullet->box += associated.box.CenterPoint();

    shared_bullet->AddComponent(bullet);
}