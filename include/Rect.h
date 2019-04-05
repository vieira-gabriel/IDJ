#ifndef RECT_H
#define RECT_H

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
  float Inclination(Rect point1, Rect point2);
  bool Contains(float valx, float);
};

#endif