#include "spring.h"

Spring::Spring(Vertex* orig, Vertex* dest){
  this->origin = orig;
  this->dest = dest;
  init = dest->position-orig->position;
  i_stretch = init.length();
}
Spring::~Spring(){
}
//returns stretch ratio in vector
float Spring::getStretch(){
  float curr_stretch = (dest->position-origin->position).length();
  //negative means compression, positive is stretch
  return curr_stretch/i_stretch - 1;
}
