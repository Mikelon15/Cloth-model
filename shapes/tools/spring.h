#pragma once

#include "common.h"
#include <QVector3D>
typedef QVector3D vec3;

class Spring{
public:
  Spring(vec3* orig, vec3* dest);
  ~Spring();
  //returns stretch ratio in vector
  float getStretch();

private:
  vec3* init;
  float i_stretch;
  vec3* origin;
  vec3* dest;
};
