#ifndef LIN_ALG_VEC_H
#define LIN_ALG_VEC_H
#pragma once
namespace lin_alg
{
    template <int L, typename T>
    struct vec;

    template <typename T>
    struct vec<3, T>
    {
        typedef vec<3, T> vec3;

        T x, y, z;

        // Constructors
        vec<3, T>() : x(0), y(0), z(0) {}
        vec<3, T>(T x, T y, T z) : x(x), y(y), z(z) {}

        T operator[](int index) const
        {
            if (index == 0)
                return x;
            if (index == 1)
                return y;
            if (index == 2)
                return z;
        }

        T &operator[](int index)
        {
            if (index == 0)
                return x;
            if (index == 1)
                return y;
            if (index == 2)
                return z;
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

        vec3 operator*(int scalar) const
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

    template<typename T>
    vec<3,T> normalize(const vec<3,T > &a) 
    {
        T magnitude = std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
        if (magnitude > 0)
        {
            return vec<3,T>(a.x / magnitude, a.y / magnitude, a.z / magnitude);
        }
        return a; // return the same vec if magnitude is 0
        // TODO: Maybe throw errors??
    }

    typedef vec<3, float> vec3;
    typedef vec<3, int> ivec3;
}

#endif