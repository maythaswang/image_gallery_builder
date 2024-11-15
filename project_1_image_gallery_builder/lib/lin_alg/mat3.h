#ifndef LIN_ALG_MAT3_H
#define LIN_ALG_MAT3_H
#pragma once

#include <cmath>
#include "./mat.h"
#include "./vec.h"

namespace lin_alg
{
    // template <int L, typename T>
    // struct mat;

    template <typename T>
    struct mat<3, T>
    {

        typedef mat<3, T> mat3;

        T m[3][3];

        // Constructors
        mat<3, T>()
        {
            m[0][0] = m[1][1] = m[2][2] = 1;
            m[0][1] = m[0][2] = m[1][0] = m[1][2] = m[2][0] = m[2][1] = 0;
        }

        mat<3, T>(T scalar)
        {
            m[0][0] = m[1][1] = m[2][2] = scalar;
            m[0][1] = m[0][2] = m[1][0] = m[1][2] = m[2][0] = m[2][1] = 0;
        }

        mat<3, T>(T a11, T a12, T a13,
                  T a21, T a22, T a23,
                  T a31, T a32, T a33)
        {
            m[0][0] = a11;
            m[0][1] = a12;
            m[0][2] = a13;
            m[1][0] = a21;
            m[1][1] = a22;
            m[1][2] = a23;
            m[2][0] = a31;
            m[2][1] = a32;
            m[2][2] = a33;
        }

        const T(&operator[](int col) const)[3]
        {
            return m[col];
        }

        T(&operator[](int col))
        [3]
        {
            return m[col];
        }

        mat3 operator+(const mat3 &other) const
        {
            return mat3(
                m[0][0] + other.m[0][0], m[0][1] + other.m[0][1], m[0][2] + other.m[0][2],
                m[1][0] + other.m[1][0], m[1][1] + other.m[1][1], m[1][2] + other.m[1][2],
                m[2][0] + other.m[2][0], m[2][1] + other.m[2][1], m[2][2] + other.m[2][2]);
        }

        mat3 operator-(const mat3 &other) const
        {
            return mat3(
                m[0][0] - other.m[0][0], m[0][1] - other.m[0][1], m[0][2] - other.m[0][2],
                m[1][0] - other.m[1][0], m[1][1] - other.m[1][1], m[1][2] - other.m[1][2],
                m[2][0] - other.m[2][0], m[2][1] - other.m[2][1], m[2][2] - other.m[2][2]);
        }

        mat3 operator*(T scalar) const
        {
            return mat3(
                m[0][0] * scalar, m[0][1] * scalar, m[0][2] * scalar,
                m[1][0] * scalar, m[1][1] * scalar, m[1][2] * scalar,
                m[2][0] * scalar, m[2][1] * scalar, m[2][2] * scalar);
        }

        mat3 operator*(int scalar) const
        {
            return mat3(
                m[0][0] * scalar, m[0][1] * scalar, m[0][2] * scalar,
                m[1][0] * scalar, m[1][1] * scalar, m[1][2] * scalar,
                m[2][0] * scalar, m[2][1] * scalar, m[2][2] * scalar);
        }

        /**
         * @brief Might need to do some transposing first before using mat multiply (if I am free maybe change to column base fully.)
         * 
         * @param other 
         * @return mat3 
         */
        mat3 operator*(const mat3 &other) const
        {
            mat3 result;
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    result.m[i][j] = 0;
                    for (int k = 0; k < 3; ++k)
                    {
                        result.m[i][j] += m[i][k] * other.m[k][j];
                    }
                }
            }
            return result;
        }

        /**
         * @brief
         * @note ASSUME COLUMN MAJOR WHEN DOING THIS
         * @example A * vec, do right multiply
         * @param v
         * @return vec<3, T>
         */
        vec<3, T> operator*(const vec<3, T> &v) const
        {
            return vec<3, T>(
                m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z,
                m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z,
                m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z);
        }
    };

    template <typename T>
    mat<3, T> transpose(const mat<3, T> &m)
    {
        mat<3, T> result;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                result[i][j] = m[j][i];
            }
        }
        return result;
    }

    typedef mat<3, float> mat3;

}

#endif