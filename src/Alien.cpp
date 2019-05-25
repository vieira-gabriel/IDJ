#include "Alien.h"

int Alien::alienCount = 0;

Alien::Alien(GameObject &associated, int nMinions) : Component(associated)
{
    Sprite *alien = new Sprite(associated, ALIEN_SOURCE);
    Collider *coliderBox = new Collider(associated);

    associated.AddComponent(alien);
    associated.AddComponent(coliderBox);

    associated.box.x -= associated.box.w / 2;
    associated.box.y -= associated.box.h / 2; // Centralizare Alien

    hp = ALIEN_HP;
    alienCount++;
    speed.x = 0;
    speed.y = 0;
    this->nMinions = nMinions;
    state = RESTING;
}

Alien::~Alien()
{
    minionArray.clear();
    alienCount--;
}

void Alien::Start()
{
    for (int i = 0; i < nMinions; i++)
    {
        GameObject *minion_GO(new GameObject());

        weak_ptr<GameObject> weak_minion = Game::GetInstance().GetCurrentState().AddObject(minion_GO);
        minionArray.emplace_back(weak_minion);
        shared_ptr<GameObject> shared_minion = weak_minion.lock();

        weak_ptr<GameObject> weak_Alien = Game::GetInstance().GetCurrentState().GetObjectPtr(&associated);

        Minion *minion = new Minion(*shared_minion, weak_Alien, (360.0 / nMinions) * i);

        shared_minion->AddComponent(minion);
    }
}

void Alien::Update(float dt)
{
    associated.angleDeg -= remainder((ALIEN_ANGLE * dt), 360.0); // Save the rest of the doble/float division, preventing it to be higher than 360 degrees
    if (PenguinBody::player != nullptr)
    {

        if (state == MOVING)
        {
            Vec2 goTo;
            goTo.x = destination.x - associated.box.x;
            goTo.y = destination.y - associated.box.y;
            float mag = goTo.Mag();
            speed.x = (goTo.x / mag) * ALIEN_SPEED;
            speed.y = (goTo.y / mag) * ALIEN_SPEED;

            float closestDistance = minionArray[0].lock()->box.CenterPoint().DistanceTo(PenguinBody::player->PenguinAt());
            int closestMinion = 0;

            for (unsigned int i = 0; i < minionArray.size(); i++)
            {

                float minionDistance = minionArray[i].lock()->box.CenterPoint().DistanceTo(PenguinBody::player->PenguinAt());

                if (minionDistance < closestDistance)
                {

                    closestDistance = minionDistance;
                    closestMinion = i;
                }
            }
            shootTime.Update(dt);
            if (minionArray[closestMinion].lock() != nullptr && (shootTime.Get() > SHOOT_COOLDOWN))
            {
                Minion *minon = static_cast<Minion *>(minionArray[closestMinion].lock()->GetComponent("Minion"));
                minon->Shoot(PenguinBody::player->PenguinAt());
                shootTime.Update(dt);
                shootTime.Restart();
            }

            if ((goTo.x > -(dt * abs(speed.x))) && (goTo.x < (dt * abs(speed.x))) && (goTo.y > -(dt * abs(speed.y))) && (goTo.y < (dt * abs(speed.y))))
            {
                speed.x = 0;
                speed.y = 0;
                state = RESTING;
                restTime.Restart();
            }

            associated.box.x += speed.x * dt;
            associated.box.y += speed.y * dt;
        }
        else if (state == RESTING)
        {

            float closestDistance = minionArray[0].lock()->box.CenterPoint().DistanceTo(PenguinBody::player->PenguinAt());
            int closestMinion = 0;

            for (unsigned int i = 0; i < minionArray.size(); i++)
            {

                float minionDistance = minionArray[i].lock()->box.CenterPoint().DistanceTo(PenguinBody::player->PenguinAt());

                if (minionDistance < closestDistance)
                {

                    closestDistance = minionDistance;
                    closestMinion = i;
                }
            }
            shootTime.Update(dt);
            if (minionArray[closestMinion].lock() != nullptr && (shootTime.Get() > SHOOT_COOLDOWN))
            {
                Minion *minon = static_cast<Minion *>(minionArray[closestMinion].lock()->GetComponent("Minion"));
                minon->Shoot(PenguinBody::player->PenguinAt());
                shootTime.Update(dt);
                shootTime.Restart();
            }

            restTime.Update(dt);
            if (restTime.Get() > ALIEN_REST)
            {
                destination.x = PenguinBody::player->PenguinAt().x;
                destination.y = PenguinBody::player->PenguinAt().y;
                state = MOVING;
                shootTime.Update(dt);
            }
        }
    }
    if (hp <= 0)
    {

        GameObject *death = new GameObject();
        std::weak_ptr<GameObject> weak_ptr = Game::GetInstance().GetCurrentState().AddObject(death);
        std::shared_ptr<GameObject> ptr = weak_ptr.lock();

        Sprite *death_sprite = new Sprite(*ptr, ALIEN_DEATH_SRC, ALIEN_DEATH_FRAME, ALIEN_DEATH_FM_TIME, ALIEN_DEATH_SF_DEST);
        Sound *death_sound = new Sound(*ptr, ALIEN_DEATH_SOUND_SRC);
        ptr->box = associated.box;
        ptr->AddComponent(death_sprite);
        ptr->AddComponent(death_sound);

        death_sound->Play(1);
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

void Alien::NotifyCollision(GameObject &other)
{
    Bullet *bullet = dynamic_cast<Bullet *>(other.GetComponent("Bullet"));

    if (bullet != nullptr && !bullet->targetsPlayer)
        hp -= bullet->GetDamage();
}