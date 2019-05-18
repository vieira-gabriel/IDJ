#include "Camera.h"

GameObject *Camera::focus;
Vec2 Camera::pos;
Vec2 Camera::speed;
InputManager &IM = InputManager::GetInstance();

void Camera::Follow(GameObject *newFocus)
{
    focus = newFocus;
}

void Camera::Unfollow()
{
    focus = nullptr;
}

void Camera::Update(float dt)
{
    speed.x = 0;
    speed.y = 0;

    if (focus != nullptr) // If focus exist, centralize it
    {
        pos.x = focus->box.x + (focus->box.w - SCR_WIDTH) / 2;
        pos.y = focus->box.y + (focus->box.h - SCR_HEIGHT) / 2;
    }
    else
    {
        if (IM.IsKeyDown(LEFT_ARROW_KEY))
            speed.x = -DEFAULT_SPEED;
        if (IM.IsKeyDown(RIGHT_ARROW_KEY))
            speed.x = DEFAULT_SPEED;
        if (IM.IsKeyDown(DOWN_ARROW_KEY))
            speed.y = DEFAULT_SPEED;
        if (IM.IsKeyDown(UP_ARROW_KEY))
            speed.y = -DEFAULT_SPEED;

        pos.x += speed.x * dt;
        pos.y += speed.y * dt;
    }
}