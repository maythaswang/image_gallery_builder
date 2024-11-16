#include "./Camera.h"
#include <iostream>
namespace ss
{
    Camera::Camera()
    {
        this->eye = lin_alg::vec3(0, 0, 3.0);
        this->center = lin_alg::vec3(0, 0, 0);
        this->up = lin_alg::vec3(0, 1.0, 0);

        this->fovy = 90.0f;
        this->aspect_w = 640.0f;
        this->aspect_h = 480.0f;
        this->z_near = 0.0001f;
        this->z_far = 2000000.0f;

        this->rotation_sensitivity = 0.2f;
        this->zoom_sensitivity = 0.1f;
        this->translation_sensitivity = 0.2f;

        this->build_view_matrix();
        this->build_projection_matrix();
    }

    void Camera::translate(GLfloat mouse_delta_x, GLfloat mouse_delta_y)
    {
        GLfloat distance = lin_alg::dot(this->center - this->eye, this->center - this->eye);
        lin_alg::vec3 direction = lin_alg::normalize(this->center - this->eye);
        lin_alg::vec3 right = lin_alg::normalize(lin_alg::cross(direction, this->up));

        GLfloat x_translate = -mouse_delta_x * this->translation_sensitivity * std::min(distance, 100000000.0f);
        GLfloat y_translate = mouse_delta_y * this->translation_sensitivity * std::min(distance, 100000000.0f);
        lin_alg::vec3 translation_vector = lin_alg::normalize(right) * x_translate + lin_alg::normalize(this->up) * y_translate;

        this->eye = this->eye + translation_vector;
        this->center = this->center + translation_vector;
        this->build_view_matrix();
    }

    void Camera::free_forward(GLfloat mouse_delta_y)
    {
        lin_alg::vec3 direction = lin_alg::normalize(this->center - this->eye);
        GLfloat zoom_power = mouse_delta_y * this->zoom_sensitivity;

        this->eye = this->eye + (direction * zoom_power);
        this->center = this->center + (direction * zoom_power);
        this->build_view_matrix();
    }

    void Camera::free_side_translate(GLfloat speed)
    {
        lin_alg::vec3 direction = lin_alg::normalize(this->center - this->eye);
        lin_alg::vec3 right = lin_alg::normalize(lin_alg::cross(direction, this->up));

        GLfloat zoom_power = speed * this->zoom_sensitivity;

        this->eye = this->eye + (right * zoom_power);
        this->center = this->center + (right * zoom_power);
        this->build_view_matrix();
    }

    // Might need to implement quarternion to mitigate some issues
    void Camera::free_rotate(GLfloat mouse_delta_x, GLfloat mouse_delta_y)
    {
        lin_alg::vec3 direction = lin_alg::normalize(this->center - this->eye);
        lin_alg::vec3 right = lin_alg::normalize(lin_alg::cross(direction, this->up));
        GLfloat yaw = -mouse_delta_x * rotation_sensitivity;  // along up-axis
        GLfloat pitch = mouse_delta_y * rotation_sensitivity; // along right-axis
        // roll: along the center-axis

        if (pitch > 89.9999f)
            pitch = -89.9999f;
        if (pitch < -89.9999f)
            pitch = 89.9999f;

        // Rotation Matrix
        lin_alg::mat4 rotationYaw = lin_alg::rotate(lin_alg::mat4(1.0f), lin_alg::radians(yaw), this->up);
        lin_alg::mat4 rotationPitch = lin_alg::rotate(rotationYaw, lin_alg::radians(pitch), right);
        lin_alg::mat3 rotation = lin_alg::mat3(rotationPitch);

        lin_alg::vec3 eye_origin = this->eye - this->center;
        lin_alg::vec3 new_eye = rotation * eye_origin;
        lin_alg::vec3 direction_to_old = eye_origin - new_eye;

        this->center = this->center + direction_to_old;
        // this->up = rotation * this->up;  // So that there is no weird rotation
        this->build_view_matrix();
    }

    void Camera::set_eye(lin_alg::vec3 eye)
    {
        this->eye = eye;
    }

    void Camera::set_center(lin_alg::vec3 center)
    {
        this->center = center;
    }

    void Camera::set_up(lin_alg::vec3 up)
    {
        this->up = up;
    }

    void Camera::set_fovy(GLfloat fovy)
    {
        this->fovy = fovy;
    }

    void Camera::set_aspect(GLfloat width, GLfloat height)
    {
        this->aspect_w = width;
        this->aspect_h = height;
        this->build_projection_matrix();
    }

    void Camera::set_z_near(GLfloat z_near)
    {
        this->z_near = z_near;
    }

    void Camera::set_z_far(GLfloat z_far)
    {
        this->z_far = z_far;
    }

    lin_alg::mat4 Camera::get_view_matrix()
    {
        return this->view_mat;
    }

    lin_alg::mat4 Camera::get_projection_matrix()
    {
        return this->projection_mat;
    }

    void Camera::build_view_matrix()
    {
        this->view_mat = lin_alg::look_at(this->eye, this->center, this->up);
    }

    void Camera::build_projection_matrix()
    {
        this->projection_mat = lin_alg::perspective(lin_alg::radians(this->fovy), this->aspect_w / this->aspect_h, this->z_near, this->z_far);
    }
}