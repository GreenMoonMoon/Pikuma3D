#ifndef PIKUMA3D_CAMERA_H
#define PIKUMA3D_CAMERA_H

#include "vector.h"

typedef struct
{
    vec3_t position;
    vec3_t rotation;
    float fov;
} camera_t;

#endif // PIKUMA3D_CAMERA_H