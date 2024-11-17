#ifndef LIN_ALG_VEC3_H
#define LIN_ALG_VEC3_H
#pragma once

#include "./vec.h"
#include "./mat.h"
#include <stdexcept>
#include <cmath>

namespace lin_alg
{
    template <typename T>
    struct vec<3, T>
    {
        typedef vec<3, T> vec3;

        T x, y, z;

        /**
         * @brief Construct a new vec<3, T> object to value <0,0,0>
         *
         */
        vec<3, T>() : x(0), y(0), z(0) {}

        /**
         * @brief Construct a new vec<3, T> object with the values provided
         */
        vec<3, T>(T x, T y, T z) : x(x), y(y), z(z) {}

        /**
         * @brief Construct a new vec<3, T> object from vec<4,T> by truncating the last value
         *
         * @param v
         */
        vec<3, T>(vec<4, T> v) : x(v.x), y(v.y), z(v.z) {}

        /**
         * @brief Copy constructor for vec<3, T>
         * @param other The vec<3, T> object to copy
         */
        vec(const vec<3, T> &other) : x(other.x), y(other.y), z(other.z) {}

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
            default:
                throw std::out_of_range("Index out of range for vec<3, T>");
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
            default:
                throw std::out_of_range("Index out of range for vec<3, T>");
            }
        }
        vec3 operator+(const int &scalar) const
        {
            return vec3(x + scalar, y + scalar, z + scalar);
        }

        vec3 operator+(const vec3 &other) const
        {
            return vec3(x + other.x, y + other.y, z + other.z);
        }

        vec3 operator-(const vec3 &other) const
        {
            return vec3(x - other.x, y - other.y, z - other.z);
        }

        vec3 operator*(T scalar) const
        {
            return vec3(x * scalar, y * scalar, z * scalar);
        }
    };

    template <typename T>
    T dot(const vec<3, T> &a, const vec<3, T> &b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    template <typename T>
    vec<3, T> cross(const vec<3, T> &a, const vec<3, T> &b)
    {
        return vec<3, T>(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x);
    }

    template <typename T>
    vec<3, T> normalize(const vec<3, T> &a)
    {
        T magnitude = std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
        if (magnitude > 0)
        {
            return vec<3, T>(a.x / magnitude, a.y / magnitude, a.z / magnitude);
        }
        return a;
    }

    /**
     * @brief Calculate the outer product of two vectors
     *
     * @tparam T
     * @param a
     * @param b
     * @return mat<3, T>
     */
    template <typename T>
    mat<3, T> outer_product(const vec<3, T> &a, const vec<3, T> &b)
    {
        return mat<3, T>(
            a.x * b.x, a.x * b.y, a.x * b.z,
            a.y * b.x, a.y * b.y, a.y * b.z,
            a.z * b.x, a.z * b.y, a.z * b.z);
    }

    /**
     * @brief vec3 of type float
     *
     */
    typedef vec<3, float> vec3;
    typedef vec<3, int> ivec3;
}

#endif