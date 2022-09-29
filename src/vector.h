#ifndef PIKUMA3D_VECTOR_H
#define PIKUMA3D_VECTOR_H

typedef struct
{
    float x, y;
} vec2_t;

typedef struct
{
    float x, y, z;
} vec3_t;


vec3_t vec3_rotate_x(vec3_t v, float a);

vec3_t vec3_rotate_y(vec3_t v, float a);

vec3_t vec3_rotate_z(vec3_t v, float a);

#endif // PIKUMA3D_VECTOR_H