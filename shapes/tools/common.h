#pragma once

#include <QVector3D>
#include <QVector2D>
#include <ostream>

typedef QVector3D vec3;
typedef QVector2D vec2;

/* Print QVector3d objects using cout. */
std::ostream &operator<<(std::ostream &str, const QVector3D &vec);
struct Vertex{
  int id;
  vec3 position;
  vec3 velocity;
  vec3 force;
  vec3 normal;
  vec2 texture;
  // //the spring vector at rest
  // std::vector<vec3> atRest;
  // //the other vertices it is is connected to by a spring
  // std::vector<Vertex*> springs;
  // //if its static, it will not be affected by forces
  bool isStatic;
};
