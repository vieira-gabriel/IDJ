#include "Collider.h"

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset) : Component(associated)
{
    this->scale = scale;
    this->offset = offset;
}

void Collider::Update(float dt)
{
    box = associated.box * scale;
    Vec2 center = Vec2(associated.box.x + associated.box.w / 2.0, associated.box.y + associated.box.h / 2.0);
    box.SetCenter(center + offset.GetRotated(associated.angleDeg * (PI / 180)));
}

void Collider::Render()
{
#ifdef DEBUG
    Vec2 center(box.CenterPoint());
    SDL_Point points[5];

    Vec2 point = (Vec2(box.x, box.y) - center).GetRotated(associated.angleDeg / (180 / PI)) + center - Camera::pos;
    points[0] = {(int)point.x, (int)point.y};
    points[4] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x + box.w, box.y) - center).GetRotated(associated.angleDeg / (180 / PI)) + center - Camera::pos;
    points[1] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x + box.w, box.y + box.h) - center).GetRotated(associated.angleDeg / (180 / PI)) + center - Camera::pos;
    points[2] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x, box.y + box.h) - center).GetRotated(associated.angleDeg / (180 / PI)) + center - Camera::pos;
    points[3] = {(int)point.x, (int)point.y};

    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}

bool Collider::Is(string type)
{
    // Return true if the type wanted is Collider
    return (type == "Collider");
}

void Collider::SetScale(Vec2 scale)
{
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset)
{
    this->offset = offset;
}
