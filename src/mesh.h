#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"

#define CUBE_VERTEX_COUNT 8
#define CUBE_FACE_COUNT (6 * 2)

extern vec3_t cube_vertices[CUBE_VERTEX_COUNT];
extern face_t cube_faces[CUBE_FACE_COUNT];

typedef struct{
    vec3_t *vertices; // Dynamic array of vertices;
    face_t *faces;    // Dynamic array of faces;
    vec3_t rotation;
} mesh_t;

extern mesh_t mesh;

void load_cube_mesh(void);

#endif // MESH_H