#ifndef VEC2_H
#define VEC2_H

#include <math.h>

#define PI 3.14159265

class Vec2
{
public:
  float x;
  float y;

  Vec2();
  Vec2(float xInit, float yInit);
  ~Vec2();

  Vec2 Sum(Vec2 vector);
  Vec2 operator+(const Vec2 &vector);
  Vec2 Sub(Vec2 vector);
  Vec2 Mul(float m);
  float Mag();
  Vec2 Normalize();
  //Inclinação de um vetor em relação ao eixo x
  Vec2 GetRotated(float angle);
};

#endif