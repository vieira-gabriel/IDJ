#pragma once

#include "Component.h"
#include "Camera.h"

using namespace std;

class CameraFollower : public Component
{
public:
    CameraFollower(GameObject &go);
    void Update(float dt);
    void Render();
    bool Is(string type);
};