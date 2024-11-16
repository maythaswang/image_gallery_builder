#ifndef LIN_ALG_UTILS_H
#define LIN_ALG_UTILS_H
#pragma once

#include "./vec3.h"
#include "./vec4.h"
#include "./mat3.h"
#include "./mat4.h"

namespace lin_alg
{

    float radians(const float degree);
    mat4 rotate(mat4 const &m, const float degrees, const vec3 &axis);
    mat4 look_at(const vec3 &eye, const vec3 &center, const vec3 &up);
    mat4 perspective(float fovy, float aspect, float zNear, float zFar);
    mat4 scale(const vec3 &s);
    mat4 translate(const vec3 &t);
}

#endif