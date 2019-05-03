#include "Face.h"

Face::Face(GameObject &associated) : Component(associated)
{
    hitpoints = 30;
}

Face::~Face()
{
}

void Face::Damage(int damage)
{
    cout << "Got damaged" << endl;
    hitpoints -= damage;
    if (hitpoints <= 0)
    {
        hitpoints = 0;
        Component::associated.RequestDelete();
        Component *comp = associated.GetComponent("Sound");
        if (comp != nullptr)
        {
            Sound *comp_sound = dynamic_cast<Sound *>(comp);
            comp_sound->Play(10);
        }
    }
}
void Face::Update(float dt)
{
    InputManager &IM = InputManager::GetInstance();
    if (IM.MousePress(LEFT_MOUSE_BUTTON))
    {
        if (associated.box.Contains(IM.GetMourseX() - Camera::pos.x, IM.GetMourseY() - Camera::pos.y))
            Damage(std::rand() % 10 + 10);
    }
}

void Face::Render()
{
}
bool Face::Is(string type)
{
    // Return true if the type wanted is Face
    bool ret = (type == "Face") ? true : false;
    return ret;
}