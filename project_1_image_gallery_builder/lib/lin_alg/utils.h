#ifndef LIN_ALG_UTILS_H
#define LIN_ALG_UTILS_H
#pragma once

#include "./vec3.h"
#include "./vec4.h"
#include "./mat3.h"
#include "./mat4.h"

/*
 * graphics helpers
 *  -> rotate
 *  -> radians
 *  -> lookat
 *  -> perspective
 */

namespace lin_alg
{
    const float PI_F=3.14159265358979f;

    float radians(const float degree){
        return degree * (PI_F / 180.0f);
    }
 
    mat3 rotate(const float degrees, const vec3 &axis)
    {
        // Rodrigues Rotation Formula
        // cos(θ)I  + (1-cos(θ)(aa^T) + sin(θ)A

        const float theta = radians(degrees);
        mat3 identity = mat3(1.0);

        mat3 aaT = lin_alg::transpose(outer_product(axis, axis));

        // ※ cos(θ) is unchanged
        // Unchanged aa^T(1-cos(θ))
        mat3 component_along_a = aaT * (1 - cos(theta));

        // Rotated Component (A * sin(θ))
        float x = axis.x;
        float y = axis.y;
        float z = axis.z;
        mat3 mat_A = mat3(0, -z, y, z, 0, -x, -y, x, 0);
        mat3 component_perpendicular_a = mat_A * sin(theta);
        mat3 v_rot = identity * cos(theta) + component_along_a + component_perpendicular_a;

        return v_rot;
    }

    mat4 look_at(const vec3 &eye, const vec3 &center, const vec3 &up)
    {
        vec3 eye_to_center = eye - center;

        vec3 w = normalize(eye_to_center);
        vec3 u = normalize(cross(normalize(up), w)); // cross product return vec3 if orthogonal
        vec3 v = cross(w, u);

        // Rotation matrix
        mat4 rot = mat4(
            u.x, u.y, u.z, 0,
            v.x, v.y, v.z, 0,
            w.x, w.y, w.z, 0,
            0, 0, 0, 1);

        // Translation Matrix
        mat4 trans = mat4(
            1, 0, 0, -eye.x,
            0, 1, 0, -eye.y,
            0, 0, 1, -eye.z,
            0, 0, 0, 1);

        // view = (Rotation)(Translation)
        mat4 viewing_mat = rot * trans;

        return viewing_mat;
    }

    mat4 perspective(float fovy, float aspect, float zNear, float zFar)
    {
        const float theta = radians(fovy) / 2;
        const float d = 1 / std::tan(theta);
        const float A = -(zNear + zFar) / (zFar - zNear);
        const float B = -2 * (zNear * zFar) / (zFar - zNear);

        mat4 projection_mat = mat4(d / aspect, 0, 0, 0,
                                 0, d, 0, 0,
                                 0, 0, A, -1,
                                 0, 0, B, 0);
        return projection_mat;
    }

    mat4 scale(const vec3& s)
    {
        mat4 scale_mat = mat4(
            s.x, 0, 0, 0,
            0, s.y, 0, 0,
            0, 0, s.z, 0,
            0, 0, 0, 1);
        return scale_mat;
    }

    mat4 translate(const vec3& t)
    {
        mat4 translate_mat = mat4(
            1, 0, 0, t.x,
            0, 1, 0, t.y,
            0, 0, 1, t.z,
            0, 0, 0, 1);
        return translate_mat;
    }
}

#endif