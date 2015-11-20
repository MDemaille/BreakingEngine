#ifndef VERTICES_STRUCTURE_H
#define VERTICES_STRUCTURE_H

#include <GL/gl.h>

struct VertexData {
  GLfloat coordinates[3];
};

struct ColorVertexData : virtual VertexData {
  GLfloat color[4];
};

struct TextureVertexData : virtual VertexData {
  GLfloat texCoordinates[2];
};

struct NormalVertexData : virtual VertexData {
  GLfloat normal[3];
};

struct CompleteColorVertexData : virtual ColorVertexData, virtual NormalVertexData {

};

struct CompleteTextureVertexData : virtual TextureVertexData,
virtual ColorVertexData, virtual NormalVertexData {

};

struct OldCompleteVertexData {
  GLfloat coordinates[3];
  GLfloat normal[3];
  GLfloat color[4];
  GLfloat texCoordinates[2];
};

template<const int N>
struct VerticesData<N> {
  int size = N;
  GLfloat x[N];
  GLfloat y[N];
  GLfloat z[N];
};

template<>
struct VerticesData<10>;

template<>
struct VerticesData<100>;

template<>
struct VerticesData<1000>;


#endif
