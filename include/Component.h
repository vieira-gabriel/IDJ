#ifndef COMPONENT_H
#define COMPONENT_H

#include "GameObject.h"
#include <iostream>
#include <string>

using namespace std;

class Component
{
  protected:
    GameObject &associated;

  public:
    Component(GameObject &associated);
    ~Component();

    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual bool Is(string type) = 0;
};

#endif