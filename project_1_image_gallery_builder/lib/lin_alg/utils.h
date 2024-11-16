#ifndef LIN_ALG_UTILS_H
#define LIN_ALG_UTILS_H
#pragma once

#include "./vec3.h"
#include "./vec4.h"
#include "./mat3.h"
#include "./mat4.h"

namespace lin_alg
{

    /**
     * @brief Convert degrees to radians value.
     * 
     * @param degree 
     * @return float 
     */
    float radians(const float degree);

    /**
     * @brief Use rodrigues rotation formula to rotate matrix m
     * 
     * @param m matrix that will be rotated 
     * @param rad magnitude of rotation
     * @param axis axis of rotation
     * @return mat4 
     */
    mat4 rotate(mat4 const &m, const float rad, const vec3 &axis);

    /**
     * @brief generate modelview matrix
     * 
     * @param eye eye direction
     * @param center center direction
     * @param up up direction
     * @return mat4 
     */
    mat4 look_at(const vec3 &eye, const vec3 &center, const vec3 &up);

    /**
     * @brief generate perspective projection matrix
     * 
     * @param fovy field of view y
     * @param aspect aspect ratio
     * @param zNear 
     * @param zFar 
     * @return mat4 
     */
    mat4 perspective(float fovy, float aspect, float zNear, float zFar);

    /**
     * @brief generate matrix for scaling
     * 
     * @param s magnitude of scaling
     * @return mat4 
     */
    mat4 scale(const vec3 &s);

    /**
     * @brief generate matrix for translation
     * 
     * @param t magnitude of translation in each direction.
     * @return mat4 
     */
    mat4 translate(const vec3 &t);
}

#endif