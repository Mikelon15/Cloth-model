#include "cloth.h"
using namespace std;
Cloth::Cloth(){
  gravity = vec3(0, -10, 0);
  m_color = vec4(1,1,1,1);
  length = 14;
  width = 14;
  nverts = length*width;
  verts = new Vertex*[width];
  for (int x = 0; x < width; x++){
    verts[x] = new Vertex[length];
    for (int y = 0; y < length; y++){
      verts[x][y] = Vertex();
      verts[x][y].id = x * width + y;
      verts[x][y].position = vec3(x, y, 0);
      verts[x][y].velocity = vec3(0, 0, 0);
      verts[x][y].force = vec3(0, 0, 0);
      verts[x][y].normal = vec3(0, 0, 1);
      verts[x][y].texture = vec2((float)x/(length-1.), (float)y/(length-1.));
      verts[x][y].isStatic = true;
    }
  }
  //this initializes the vbo information, but vertices and normals
  // will need need to be updated in the vbo after every update
  vertices = new vec3[nverts];
  normals  = new vec3[nverts];
  texture  = new vec2[nverts];
  for (int x = 0; x < width; x++){
    for (int y = 0; y < length; y++){
      vertices[x*width+y] = verts[x][y].position;
      normals[x*width+y]  = verts[x][y].normal;
      texture[x*width+y]  = verts[x][y].texture;
    }
  }
  //creates indices array to draw picure
  ninds = width*(length+length-2)+ 2*(length-2);
  indices = new unsigned short[ninds];
  int i = 0;
  for (int x = 0; x < width-1; x++){
    //inserts the last and first index of the row
    //to move to the next strip of triangles
    if (x != 0){
      indices[i++] = x*width+width-1;
      indices[i++] = x*width;
    }
    for (int y = 0; y < length; y++){
      indices[i++] = x*width+y;
      indices[i++] = (x+1)*width+y;
    }
  }
  if(initVBO()){
    m_vbo->bind();
    m_vbo->allocate(nverts*sizeof(vec3)
                  + nverts*sizeof(vec3)
                  + nverts*sizeof(vec2));
    m_vbo->write(0, vertices, nverts*sizeof(vec3));
    m_vbo->write(nverts*sizeof(vec3), normals, nverts*sizeof(vec3));
    m_vbo->write(nverts*sizeof(vec3)+nverts*sizeof(vec3), texture, nverts*sizeof(vec2));
    m_vbo->release();
    //write indices to ebo
    m_ebo->bind();
    m_ebo->allocate(indices, ninds*sizeof(unsigned short));
    m_ebo->release();
  }
  delete [] vertices; vertices=NULL;
  delete [] texture; texture=NULL;
}

/*this will become a function to pack the
  vertices position into a position array
  that gets passed to the gpu for the tube processing
*/
void Cloth::updateVBO(){
  for (int x = 0; x < width; x++){
    for (int y = 0; y < length; y++){
      vertices[x*width+y] = verts[x][y].position;
      normals[x*width+y]  = verts[x][y].normal;
    }
  }
  m_vbo->write(0, vertices, nverts*sizeof(vec3));
  m_vbo->write(nverts*sizeof(vec3), normals, nverts*sizeof(vec3));
}
// QVector3D getSpringForces(Vertex* v){
// }
// QVector3D getSelfColForces(Vertex* v){
// }
// QVector3D getObjColForces(Vertex* v, Sphere* spheres, int amount){
// }
Cloth::~Cloth(){

  if (m_vbo) {
    m_vbo->release();
    delete m_vbo;
    m_vbo = NULL;
  }
  if (m_vao) {
    m_vao->release();
    delete m_vao;
    m_vao = NULL;
  }
}
void Cloth::draw(QOpenGLShaderProgram* prog){
  if (!prog) {
    return;
  }
  if (firstDraw){
    setupVAO(prog);
    firstDraw=false;
  }
  m_vao->bind();
  m_vbo->bind();
  m_ebo->bind();

  glDrawElements(GL_TRIANGLE_STRIP, ninds, GL_UNSIGNED_SHORT, (void*)0);

  m_ebo->release();
  m_vbo->release();
  m_vao->release();
}
bool Cloth::initVBO(){
  m_vao = new QOpenGLVertexArrayObject();
  bool ok = m_vao->create();
  if (!ok) {
    return false;
  }

  m_vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  ok = m_vbo->create();
  if (!ok) {
    return false;
  }
  m_vbo->setUsagePattern(QOpenGLBuffer::DynamicDraw);

  m_ebo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
  ok = m_ebo->create();
  if (!ok) {
    return false;
  }
  m_ebo->setUsagePattern(QOpenGLBuffer::StaticDraw);

  return ok;
}
void Cloth::setupVAO(QOpenGLShaderProgram* prog){

  m_vbo->bind();
  m_vao->bind();
  prog->setUniformValue("vColor", m_color);
  prog->setUniformValue("vSColor", vec4(1,1,1,1));
  prog->enableAttributeArray("vPosition");
  prog->setAttributeBuffer("vPosition", GL_FLOAT, 0, 3, 0);
  prog->enableAttributeArray("vNormal");
  prog->setAttributeBuffer("vNormal", GL_FLOAT,
    nverts*sizeof(vec3), 3, 0);
  prog->enableAttributeArray("vTexture");
  prog->setAttributeBuffer("vTexture", GL_FLOAT,
    nverts*2*sizeof(vec3), 2, 0);
  m_vbo->release();
  m_vao->release();
}
