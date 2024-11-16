#ifndef LIN_ALG_H
#define LIN_ALG_H
#pragma once
#include "./vec3.h"
#include "./vec4.h"
#include "./mat3.h"
#include "./mat4.h"
#include "./utils.h"

/**
 * LIBRARY FOR BASIC LINEAR ALGEBRA OPERATIONS FOR GRAPHICS PROGRAMMING
 * Use lin_alg namespace to access types and functions provided
 * The matrices are formatted in ROW-MAJOR Form. 
 * 
 * NOTE - You will need to transpose the matrix when sending this to shader
 * 
 * The types that are provided includes 
 * - vec3
 * - vec4
 * - mat3 
 * - mat4 
 * 
 * Along basic functionalities to help with graphics works including 
 * - vec, mat addition
 * - vec, mat subtraction
 * - vec, mat scalar multiplication
 * 
 * - matrix multiplication 
 * - outer product
 * - normalize
 * - dot product
 * - cross product 
 * - transpose
 * 
 * - radians
 * - rotate
 * - look_at
 * - perspective
 * - scale
 * - translate
 */
namespace lin_alg
{
    
} 
#endif