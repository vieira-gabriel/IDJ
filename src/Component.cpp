#include "Component.h"

Component::Component(GameObject &associated)
{
}

Component::~Component()
{
}

virtual void Component::Update(float dt)
{
}

virtual void Component::Render()
{
}

virtual bool Component::Is(string type)
{
}