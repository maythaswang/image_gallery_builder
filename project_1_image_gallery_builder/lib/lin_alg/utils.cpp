#include "./utils.h"

namespace lin_alg
{
    float radians(const float degree)
    {
        const float PI_F = 3.14159265358979f;
        return degree * (PI_F / 180.0f);
    }

    mat4 rotate(mat4 const &m, const float rad, const vec3 &axis)
    {
        // Rodrigues Rotation Formula
        // cos(θ)I  + (1-cos(θ)(aa^T) + sin(θ)A

        vec3 axis_n = normalize(axis);

        mat3 identity = mat3(1.0);
        mat3 aaT = outer_product(axis_n, axis_n);

        // ※ cos(θ) is unchanged
        // Unchanged aa^T(1-cos(θ))
        mat3 component_along_a = aaT * (1 - cos(rad));

        // Rotated Component (A * sin(θ))
        float x = axis_n.x;
        float y = axis_n.y;
        float z = axis_n.z;
        mat3 mat_A = mat3(0, -z, y, z, 0, -x, -y, x, 0);
        mat3 component_perpendicular_a = mat_A * sin(rad);
        mat3 v_rot = identity * cos(rad) + component_along_a + component_perpendicular_a;

        mat4 m_out = mat4(v_rot * mat3(m));
        m_out[0][3] = m[0][3];
        m_out[1][3] = m[1][3];
        m_out[2][3] = m[2][3];
        m_out[3][0] = m[3][0];
        m_out[3][1] = m[3][1];
        m_out[3][2] = m[3][2];
        m_out[3][3] = m[3][3];

        return m_out;
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
        const float theta = fovy / 2.0f;
        const float d = 1 / std::tan(theta);
        const float A = -(zNear + zFar) / (zFar - zNear);
        const float B = -2 * (zNear * zFar) / (zFar - zNear);

        mat4 projection_mat = mat4(d / aspect, 0, 0, 0,
                                   0, d, 0, 0,
                                   0, 0, A, B,
                                   0, 0, -1, 0);
        return projection_mat;
    }

    mat4 scale(const vec3 &s)
    {
        mat4 scale_mat = mat4(
            s.x, 0, 0, 0,
            0, s.y, 0, 0,
            0, 0, s.z, 0,
            0, 0, 0, 1);
        return scale_mat;
    }

    mat4 translate(const vec3 &t)
    {
        mat4 translate_mat = mat4(
            1, 0, 0, t.x,
            0, 1, 0, t.y,
            0, 0, 1, t.z,
            0, 0, 0, 1);
        return translate_mat;
    }
}