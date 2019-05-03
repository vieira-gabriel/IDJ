#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <Component.h>
#include <vector>
#include <Rect.h>
#include <iostream>
#include <memory>

using namespace std;
class Component;

class GameObject
{
private:
  vector<shared_ptr<Component>> components;
  bool isDead;
  bool started;

public:
  Rect box;

  GameObject();
  ~GameObject();

  void Update(float dt);
  void Render();
  bool IsDead();
  void RequestDelete();
  void AddComponent(Component *cpt);
  void RemoveComponent(Component *cpt);
  Component *GetComponent(string type);
  void Start();
};

#endif