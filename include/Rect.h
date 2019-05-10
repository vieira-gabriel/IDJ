#pragma once

#include "Vec2.h"

class Vec2;

class Rect
{
public:
  float x;
  float y;
  float w;
  float h;

  Rect();
  Rect(float x, float y, float w, float h);
  ~Rect();
  float Inclination(Rect rect);
  bool Contains(float valx, float);
  Vec2 CenterPoint();
  Rect operator-(const Vec2 &vec);
  Rect operator+(const Vec2 &vec);
  void operator+=(const Vec2 &vec);
  void operator-=(const Vec2 &vec);
  void operator=(const Rect &rec);
};