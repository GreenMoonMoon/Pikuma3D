#include "vector.h"
#include <math.h>

/// @brief Rotate a vector around the X axis
/// @param v Vector to rotate
/// @param a Angle of rotation
/// @return Rotated Vector
vec3_t vec3_rotate_x(vec3_t v, float a){
    vec3_t r = {
        .x = v.x,
        .y = v.y * cos(a) - v.z * sin(a),
        .z = v.y * sin(a) + v.z * cos(a)
    };
    return r;
}

/// @brief Rotate a vector around the Y axis
/// @param v Vector to rotate
/// @param a Angle of rotation
/// @return Rotated Vector
vec3_t vec3_rotate_y(vec3_t v, float a){
    vec3_t r = {
        .x = v.x * cos(a) - v.z * sin(a),
        .y = v.y,
        .z = v.x * sin(a) + v.z * cos(a)
    };
    return r;
}

/// @brief Rotate a vector around the Z axis
/// @param v Vector to rotate
/// @param a Angle of rotation
/// @return Rotated Vector
vec3_t vec3_rotate_z(vec3_t v, float a){
    vec3_t r = {
        .x = v.x * cos(a) - v.y * sin(a),
        .y = v.x * sin(a) + v.y * cos(a),
        .z = v.z
    };
    return r;
}