#ifndef CAM_FOLLOWER_H
#define CAM_FOLLOWER_H

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

#endif