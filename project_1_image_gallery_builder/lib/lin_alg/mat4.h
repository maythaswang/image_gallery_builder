#ifndef LIN_ALG_MAT4_H
#define LIN_ALG_MAT4_H
#pragma once

#include <cmath>
#include "./mat.h"
#include "./vec.h"

namespace lin_alg
{
    template <typename T>
    struct mat<4, T>
    {
        typedef mat<4, T> mat4;

        T m[4][4];

        // Constructors
        mat<4, T>()
        {
            m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1;
            m[0][1] = m[0][2] = m[0][3] = m[1][0] = m[1][2] = m[1][3] = m[2][0] = m[2][1] = m[2][3] = m[3][0] = m[3][1] = m[3][2] = 0;
        }

        mat<4, T>(T scalar)
        {
            m[0][0] = m[1][1] = m[2][2] = m[3][3] = scalar;
            m[0][1] = m[0][2] = m[0][3] = m[1][0] = m[1][2] = m[1][3] = m[2][0] = m[2][1] = m[2][3] = m[3][0] = m[3][1] = m[3][2] = 0;
        }

        mat<4, T>(T a11, T a12, T a13, T a14,
                  T a21, T a22, T a23, T a24,
                  T a31, T a32, T a33, T a34,
                  T a41, T a42, T a43, T a44)
        {
            m[0][0] = a11; m[0][1] = a12; m[0][2] = a13; m[0][3] = a14;
            m[1][0] = a21; m[1][1] = a22; m[1][2] = a23; m[1][3] = a24;
            m[2][0] = a31; m[2][1] = a32; m[2][2] = a33; m[2][3] = a34;
            m[3][0] = a41; m[3][1] = a42; m[3][2] = a43; m[3][3] = a44;
        }

        const T(&operator[](int col) const)[4]
        {
            return m[col];
        }

        T(&operator[](int col))[4]
        {
            return m[col];
        }

        mat4 operator+(const mat4 &other) const
        {
            return mat4(
                m[0][0] + other[0][0], m[0][1] + other[0][1], m[0][2] + other[0][2], m[0][3] + other[0][3],
                m[1][0] + other[1][0], m[1][1] + other[1][1], m[1][2] + other[1][2], m[1][3] + other[1][3],
                m[2][0] + other[2][0], m[2][1] + other[2][1], m[2][2] + other[2][2], m[2][3] + other[2][3],
                m[3][0] + other[3][0], m[3][1] + other[3][1], m[3][2] + other[3][2], m[3][3] + other[3][3]);
        }

        mat4 operator-(const mat4 &other) const
        {
            return mat4(
                m[0][0] - other[0][0], m[0][1] - other[0][1], m[0][2] - other[0][2], m[0][3] - other[0][3],
                m[1][0] - other[1][0], m[1][1] - other[1][1], m[1][2] - other[1][2], m[1][3] - other[1][3],
                m[2][0] - other[2][0], m[2][1] - other[2][1], m[2][2] - other[2][2], m[2][3] - other[2][3],
                m[3][0] - other[3][0], m[3][1] - other[3][1], m[3][2] - other[3][2], m[3][3] - other[3][3]);
        }

        mat4 operator*(T scalar) const
        {
            return mat4(
                m[0][0] * scalar, m[0][1] * scalar, m[0][2] * scalar, m[0][3] * scalar,
                m[1][0] * scalar, m[1][1] * scalar, m[1][2] * scalar, m[1][3] * scalar,
                m[2][0] * scalar, m[2][1] * scalar, m[2][2] * scalar, m[2][3] * scalar,
                m[3][0] * scalar, m[3][1] * scalar, m[3][2] * scalar, m[3][3] * scalar);
        }

        mat4 operator*(int scalar) const
        {
            return mat4(
                m[0][0] * scalar, m[0][1] * scalar, m[0][2] * scalar, m[0][3] * scalar,
                m[1][0] * scalar, m[1][1] * scalar, m[1][2] * scalar, m[1][3] * scalar,
                m[2][0] * scalar, m[2][1] * scalar, m[2][2] * scalar, m[2][3] * scalar,
                m[3][0] * scalar, m[3][1] * scalar, m[3][2] * scalar, m[3][3] * scalar);
        }

        // TODO: FIX LATER
        mat4 operator*(const mat4 &other) const
        {
            mat4 result;
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    result.m[i][j] = 0;
                    for (int k = 0; k < 4; ++k)
                    {
                        result[i][j] += m[i][k] * other[k][j];
                    }
                }
            }
            return result;
        }

        vec<4, T> operator*(const vec<4, T> &v) const
        {
            return vec<4, T>(
                m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w,
                m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w,
                m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2] * v.w,
                m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z + m[3][3] * v.w);
        }
    };

    template <typename T>
    mat<4, T> transpose(const mat<4, T> &m)
    {
        mat<4, T> result;
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                result[i][j] = m[j][i];
            }
        }
        return result;
    }

    typedef mat<4, float> mat4;
}

#endif
