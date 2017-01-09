#pragma once


#include <QtOpenGL>
#include <cmath>
#include <iostream>
#include "sphere.h"
#include "tools/common.h"
#include "tools/ray.h"

typedef QVector2D vec2;
typedef QVector3D vec3;
typedef QVector4D vec4;
class Cloth{

public:
  Cloth();
  ~Cloth();
  void draw(QOpenGLShaderProgram* prog);
  // void update(Sphere* spheres, int amount);

private:
  bool initVBO();
  void updateVBO();
  void setupVAO(QOpenGLShaderProgram* prog);
  // QVector3D getSpringForces(Vertex* v);
  // QVector3D getSelfColForces(Vertex* v);
  // QVector3D getObjColForces(Vertex* v, Sphere* spheres, int amount);

protected:
  int length, width, nverts, ninds;
  unsigned short* indices;
  vec4 m_color;
  QVector3D gravity;
  Vertex** verts;
  bool firstDraw;

  vec3* vertices;
  vec3* normals;
  vec2* texture;
  QOpenGLBuffer *m_vbo;
  QOpenGLBuffer *m_ebo;
  QOpenGLVertexArrayObject *m_vao;
};
