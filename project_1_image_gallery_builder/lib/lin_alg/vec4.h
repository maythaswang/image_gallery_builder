#ifndef LIN_ALG_VEC4_H
#define LIN_ALG_VEC4_H
#pragma once

#include "./vec.h"
#include "./mat.h"

#include <stdexcept>
#include <cmath>

namespace lin_alg
{
    template <typename T>
    struct vec<4, T>
    {
        typedef vec<4, T> vec4;

        T x, y, z, w;

        // Constructors
        vec<4, T>() : x(0), y(0), z(0), w(0) {}
        vec<4, T>(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
        vec<4, T>(vec<3, T> v) : x(v.x), y(v.y), z(v.z), w(0) {}

        // Operators
        T operator[](int index) const
        {
            switch (index)
            {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            case 3:
                return w;
            default:
                throw std::out_of_range("Index out of range for vec<4, T>");
            }
        }

        T &operator[](int index)
        {
            switch (index)
            {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            case 3:
                return w;
            default:
                throw std::out_of_range("Index out of range for vec<4, T>");
            }
        }

        vec4 operator+(const vec4 &other) const
        {
            return vec4(x + other.x, y + other.y, z + other.z, w + other.w);
        }

        vec4 operator-(const vec4 &other) const
        {
            return vec4(x - other.x, y - other.y, z - other.z, w - other.w);
        }

        vec4 operator*(T scalar) const
        {
            return vec4(x * scalar, y * scalar, z * scalar, w * scalar);
        }

        vec4 operator*(int scalar) const
        {
            return vec4(x * scalar, y * scalar, z * scalar, w * scalar);
        }
    };

    template <typename T>
    T dot(const vec<4, T> &a, const vec<4, T> &b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    template <typename T>
    vec<4, T> normalize(const vec<4, T> &a)
    {
        T magnitude = std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
        if (magnitude > 0)
        {
            return vec<4, T>(a.x / magnitude, a.y / magnitude, a.z / magnitude, a.w / magnitude);
        }
        return a;
    }

    // Outer product of two vec4
    template <typename T>
    mat<4, T> outer_product(const vec<4, T> &a, const vec<4, T> &b)
    {
        return mat<4, T>(
            a.x * b.x, a.x * b.y, a.x * b.z, a.x * b.w,
            a.y * b.x, a.y * b.y, a.y * b.z, a.y * b.w,
            a.z * b.x, a.z * b.y, a.z * b.z, a.z * b.w,
            a.w * b.x, a.w * b.y, a.w * b.z, a.w * b.w);
    }

    typedef vec<4, float> vec4;
    typedef vec<4, int> ivec4;
}

#endif
