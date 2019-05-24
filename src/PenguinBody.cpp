#include "PenguinBody.h"

PenguinBody *PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject &associated) : Component(associated)
{
    Sprite *penguinSprite = new Sprite(associated, PENGUIN_BODY_SOURCE);
    Collider *coliderBox = new Collider(associated);

    associated.AddComponent(penguinSprite);
    associated.AddComponent(coliderBox);

    speed = Vec2(0, 0);
    this->linearSpeed = 0.0;
    angle = 0;
    hp = PENGUIN_HP;

    this->player = this;
}

PenguinBody::~PenguinBody()
{
    this->player = nullptr;
}
void PenguinBody::Start()
{
    GameObject *cannon_GO = new GameObject();
    pcannon = Game::GetInstance().GetCurrentState().AddObject(cannon_GO);
    shared_ptr<GameObject> shared_cannon = pcannon.lock();

    PenguinCannon *cannon = new PenguinCannon(*shared_cannon, Game::GetInstance().GetCurrentState().GetObjectPtr(&associated));

    shared_cannon->box = associated.box;

    shared_cannon->AddComponent(cannon);
}

void PenguinBody::Update(float dt)
{
    InputManager &input = InputManager::GetInstance();

    if (input.IsKeyDown(W_KEY))
    {
        linearSpeed += PENGUIN_ACCELERATION * dt;
        if (linearSpeed > MAXIMUM_SPEED_MOD)
            linearSpeed = MAXIMUM_SPEED_MOD;
    }
    else if (input.IsKeyDown(S_KEY))
    {
        linearSpeed -= PENGUIN_ACCELERATION * dt;
        if (linearSpeed < -MAXIMUM_SPEED_MOD)
            linearSpeed = -MAXIMUM_SPEED_MOD;
    }
    else
    {
        if (linearSpeed <= 0.2 && linearSpeed >= -0.2)
            linearSpeed = 0.0;
        else
        {
            int speed_signal = linearSpeed / abs(linearSpeed);

            linearSpeed -= speed_signal * 2 * (PENGUIN_ACCELERATION * dt);
        }
    }

    if (input.IsKeyDown(A_KEY))
        angle -= PENGUIN_ANGULAR_VEL * dt;
    else if (input.IsKeyDown(D_KEY))
        angle += PENGUIN_ANGULAR_VEL * dt;

    if ((angle >= 359 * (PI / 180)) || (-angle >= 359 * (PI / 180)))
        angle = 0;

    speed = Vec2(linearSpeed, 0);
    speed.GetRotated(angle);

    associated.box += speed * dt;
    associated.angleDeg = angle * (180 / PI);

    if (hp <= 0)
    {
        hp = 0;
        associated.RequestDelete();

        shared_ptr<GameObject> shared_cannon = pcannon.lock();

        if (shared_cannon != nullptr)
            shared_cannon->RequestDelete();

        Camera::Unfollow();

        GameObject *go = (new GameObject());
        weak_ptr<GameObject> weak_go = Game::GetInstance().GetCurrentState().AddObject(go);
        shared_ptr<GameObject> shared_go = weak_go.lock();

        Sprite *death_sprite = new Sprite(*shared_go, PENGUIN_DEATH_SRC, PENGUIN_DEATH_FRAME, PENGUIN_DEATH_FM_TIME, PENGUIN_DEATH_SF_DEST);
        Sound *death_sound = new Sound(*shared_go, PENGUIN_DEATH_SOUND_SRC);

        shared_go->box = associated.box;
        shared_go->AddComponent(death_sprite);
        shared_go->AddComponent(death_sound);

        death_sound->Play(1);
    }
}

void PenguinBody::Render()
{
}

bool PenguinBody::Is(string type)
{
    return (type == "PenguinBody");
}

void PenguinBody::NotifyCollision(GameObject &other)
{
    Bullet *bullet = dynamic_cast<Bullet *>(other.GetComponent("Bullet"));

    if (bullet != nullptr && bullet->targetsPlayer)
        hp -= bullet->GetDamage();
}

Vec2 PenguinBody::PenguinAt()
{
    return associated.box.CenterPoint();
}