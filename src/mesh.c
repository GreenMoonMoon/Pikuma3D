#include "mesh.h"
#include "array.h"
#include "obj_parser.h"
#include <stdio.h>
#include <stdlib.h>

mesh_t mesh = {
    .vertices = NULL,
    .faces = NULL,
    .rotation = {.x = 0.0f, .y = 0.0f, .z = 0.0f}
};

vec3_t cube_vertices[CUBE_VERTEX_COUNT] = {
    {.x = -0.5f, .y = -0.5f, .z =  0.5f},
    {.x =  0.5f, .y = -0.5f, .z =  0.5f},
    {.x =  0.5f, .y =  0.5f, .z =  0.5f},
    {.x = -0.5f, .y =  0.5f, .z =  0.5f},
    {.x = -0.5f, .y = -0.5f, .z = -0.5f},
    {.x =  0.5f, .y = -0.5f, .z = -0.5f},
    {.x =  0.5f, .y =  0.5f, .z = -0.5f},
    {.x = -0.5f, .y =  0.5f, .z = -0.5f}
};

face_t cube_faces[CUBE_FACE_COUNT] = {
    {0, 1, 2}, {2, 3, 0},
    {1, 5, 6}, {6, 2, 1},
    {5, 4, 7}, {7, 6, 5},
    {4, 0, 3}, {3, 7, 4},
    {3, 2, 6}, {6, 7, 3},
    {0, 1, 5}, {5, 4, 0}
};

void load_cube_mesh(void) {
    // mesh.vertices = array_hold(cube_vertices, CUBE_VERTEX_COUNT, sizeof(vec3_t)),
    // mesh.faces = array_hold(cube_faces, CUBE_FACE_COUNT, sizeof(face_t)),
    for(int i = 0; i < CUBE_VERTEX_COUNT; i++) {
        array_push(mesh.vertices, cube_vertices[i]);
    }
    for(int i = 0; i < CUBE_FACE_COUNT; i++) {
        array_push(mesh.faces, cube_faces[i]);
    }

    mesh.rotation.x = 0.01f;
    mesh.rotation.y = 0.1f;
    mesh.rotation.z = 0.05f;
}

void load_obj_file(char *file_path) {
    FILE *fp;
    char * line = NULL;
    size_t length = 0;
    size_t read = 0;

    fp = fopen(file_path, "r");
    if (fp == NULL) return;

    

    fclose(fp);
}