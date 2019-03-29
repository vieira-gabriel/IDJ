#include "GameObject.h"

std::vector<Component *>::iterator it;

GameObject::GameObject()
{
    isDead = false;
}

GameObject::~GameObject()
{
    while (!components.empty())
        components.pop_back(); // Remove and destroy last element of the vector
    if (components.empty())
        components.clear();
}

void GameObject::Update(float dt)
{
    for (int i = 0; i < components.size(); i++)
        components[i]->Update(dt);
}

void GameObject::Render()
{
    for (int i = 0; i < components.size(); i++)
        components[i]->Render();
}

bool GameObject::IsDead()
{
    return isDead;
}

void GameObject::RequestDelete()
{
    isDead = true;
}

void GameObject::AddComponent(Component *cpt)
{
    components.push_back(cpt);
}

void GameObject::RemoveComponent(Component *cpt)
{
    if (!components.empty())
        components.pop_back();
}

Component *GameObject::GetComponent(string type)
{
}