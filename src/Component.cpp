#include "Component.h"

Component::Component(GameObject &associated) : associated(associated)
{
}

Component::~Component()
{
}

void Component::Update(float dt)
{
}

void Component::Render()
{
}

bool Component::Is(string type)
{
    // Return true if the type wanted is Component
    bool ret = (type == "Component") ? true : false;
    return ret;
}

void Component::Start()
{
}