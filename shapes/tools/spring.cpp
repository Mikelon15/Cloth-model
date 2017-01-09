#include "spring.h"

Cloth::Cloth(Vertex* orig, Vertex* dest){
  this->origin = orig;
  this->dest = dest;
  init = dest-orig;
  i_stretch = init.length();
}
Cloth::~Cloth(){
}
//returns stretch ratio in vector
float Cloth::getStretch(){
  float curr_stretch = (dest-orig).length();
  //negative means compression, positive is stretch
  return curr_stretch/i_stretch - 1;
}
