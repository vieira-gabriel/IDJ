#include "CameraFollower.h"

CameraFollower::CameraFollower(GameObject &go) : Component(go)
{
}

void CameraFollower::Update(float dt)
{
    associated.box.x = -Camera::pos.x;
    associated.box.y = -Camera::pos.y;
}

void CameraFollower::Render()
{
}

bool CameraFollower::Is(string type)
{
    // Return true if the type wanted is CameraFollower
    bool ret = (type == "CameraFollower") ? true : false;
    return ret;
}
