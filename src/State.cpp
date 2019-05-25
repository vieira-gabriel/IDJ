#include <State.h>

std::vector<std::unique_ptr<GameObject>>::iterator it;

State::State()
{
    popRequested = 0;
    quitRequested = 0;
    started = 0;
}

State::~State()
{
    objectArray.clear();
}

weak_ptr<GameObject> State::AddObject(GameObject *go)
{
    shared_ptr<GameObject> shared = make_shared<GameObject>(*go);

    objectArray.push_back(shared);
    if (started)
        objectArray.back()->Start();

    return weak_ptr<GameObject>(objectArray.back());
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject *go)
{
    for (unsigned int i = 0; i < objectArray.size(); i++)
    {
        if (objectArray[i].get() == go)
            return (weak_ptr<GameObject>)objectArray[i];
    }
    return weak_ptr<GameObject>();
}

bool State::QuitRequested()
{
    return quitRequested;
}
bool State::PopRequested()
{
    return popRequested;
}

void State::StartArray()
{
    for (unsigned int i = 0; i < objectArray.size(); i++)
    {
        objectArray[i]->Start();
    }
}

void State::UpdateArray(float dt)
{
    for (unsigned int i = 0; i < objectArray.size(); i++)
    {
        if (objectArray[i]->IsDead())
            objectArray.erase(objectArray.begin() + i);
    }
    for (unsigned int i = 0; i < objectArray.size(); i++)
    {
        objectArray[i]->Update(dt);
    }
}

void State::RenderArray()
{
    for (unsigned int i = 0; i < objectArray.size(); i++)
    {
        objectArray[i]->Render();
    }
}