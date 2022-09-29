#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"

typedef struct {
    int indices[3];
} face_t;

typedef struct {
    vec2_t points[3];
} triangle_t;

#endif // TRIANGLE_H