#include "GameObject.h"

GameObject::GameObject()
{
    //Atribute false to isDead
    isDead = false;
    started = false;
    components.clear();
    box = Rect();
    angleDeg = 0;
}

GameObject::~GameObject()
{
    // Removes and destroy elements of the vector
    components.erase(components.begin(), components.end());
    // Removes all elements from the vector (which are destroyed), leaving the container
    // with a size of 0, if components is empty;
    if (components.empty())
        components.clear();
}

void GameObject::Update(float dt)
{
    // Update all components of the vector
    for (unsigned int i = 0; i < components.size(); i++)
    {
        components[i]->Update(dt);
    }
}

void GameObject::Render()
{
    // Render all components of the vector
    for (unsigned int i = 0; i < components.size(); i++)
        components[i]->Render();
}

bool GameObject::IsDead()
{
    // Return the contents of isDead
    return isDead;
}

void GameObject::RequestDelete()
{
    // Atribute true to isDead
    isDead = true;
}

void GameObject::AddComponent(Component *cpt)
{
    // If the new component is not a null pointer, it'll be added in the vector
    if (cpt != nullptr)
        components.emplace_back(cpt);
    if (started)
        components.back()->Start();
}

void GameObject::RemoveComponent(Component *cpt)
{
    // Go through the vector searching for the component cpt and erase it when cpt
    // is found
    for (unsigned int i = 0; i < components.size(); i++)
    {
        if (components[i].get() == cpt)
            components.erase(components.begin() + i);
    }
}

Component *GameObject::GetComponent(string type)
{
    // Go through the vector seraching for the type of component that is requested
    // and return that component
    for (unsigned int i = 0; i < components.size(); i++)
    {
        if (components[i]->Is(type))
        {
            return components[i].get(); // Converte unique_ptr para ponteiro
        }
    }
    return nullptr;
}

void GameObject::Start()
{
    if (!started)
    {
        for (unsigned int i = 0; i < components.size(); i++)
        {
            components[i]->Start();
            components[i]->started = true;
        }
        started = true;
    }
}

void GameObject::NotifyCollision(GameObject &other)
{
    for (unsigned int i = 0; i < components.size(); i++)
        components[i]->NotifyCollision(other);
}