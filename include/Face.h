#ifndef FACE_H
#define FACE_H

#include "Component.h"
#include "GameObject.h"
#include "Sound.h"
#include "InputManager.h"
#include "Camera.h"
#include <iostream>
#include <string>

using namespace std;

class Face : public Component
{
private:
  int hitpoints;

public:
  Face(GameObject &associated);
  ~Face();

  void Damage(int damage);
  void Update(float dt);
  void Render();
  bool Is(string type);
};

#endif