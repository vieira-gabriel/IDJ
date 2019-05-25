#pragma once

#include <GameObject.h>
#include <iostream>
#include <string>

using namespace std;

class GameObject;

class Component
{
protected:
  GameObject &associated;

public:
  bool started;

  Component(GameObject &associated);
  virtual ~Component();

  virtual void Update(float dt) = 0;
  virtual void Render() = 0;
  virtual bool Is(string type) = 0;
  virtual void Start();
  virtual void NotifyCollision(GameObject &other);
};