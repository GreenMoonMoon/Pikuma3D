#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"

#define MESH_VERTEX_COUNT 8
extern vec3_t cube_vertices[MESH_VERTEX_COUNT];

#define MESH_FACE_COUNT (6 * 2)
extern face_t cube_faces[MESH_FACE_COUNT];

#endif // MESH_H