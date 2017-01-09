#ifndef SPRING_H
#define SPRING_H

#include "common.h"

public:
  Cloth(Vertex orig, Vertex dest);
  ~Cloth();
  //returns stretch ratio in vector
  float getStretch();

private:
  vec3 init;
  float istretch; 
  Vertex* origin;
  Vertex* dest;

#endif /* end of include guard: SPRING_H */
