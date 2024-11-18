#include "./GeometryBuilder.h"
#include <iostream>

GeometryBuilder::GeometryBuilder()
{
}
GeometryBuilder::~GeometryBuilder()
{
}

ss::Mesh GeometryBuilder::init_plane(GLfloat width, GLfloat depth, GLuint material_id)
{
    ss::Mesh mesh;

    const GLuint n_vert = 4;
    const GLuint n_inds = 6;
    GLfloat half_width = width * 0.5f;
    GLfloat half_depth = depth * 0.5f;

    std::vector<lin_alg::vec3> vertices{
        lin_alg::vec3(-half_width, 0, -half_depth),
        lin_alg::vec3(-half_width, 0, half_depth),
        lin_alg::vec3(half_width, 0, -half_depth),
        lin_alg::vec3(half_width, 0, half_depth)};

    std::vector<lin_alg::ivec3> indices{
        lin_alg::ivec3(0, 1, 3),
        lin_alg::ivec3(0, 2, 3),
    };

    std::vector<lin_alg::vec3> normals{
        lin_alg::vec3(0, 0, 1),
        lin_alg::vec3(0, 0, 1),
        lin_alg::vec3(0, 0, 1),
        lin_alg::vec3(0, 0, 1)};

    std::vector<GLfloat> tex_coords{
        0, 0,
        0, 1,
        1, 0,
        1, 1};
    mesh.vertices = vertices;
    mesh.indices = indices;
    mesh.normals = normals;
    mesh.tex_coord = tex_coords;
    mesh.mat_id = material_id;
    return mesh;
}

ss::Mesh GeometryBuilder::init_box(GLfloat width, GLfloat height, GLfloat depth, GLfloat mat_id)
{
    const GLuint n_vert = 8;
    const GLuint n_inds = 12;

    GLfloat half_width = width * 0.5f;
    GLfloat half_height = height * 0.5f;
    GLfloat half_depth = depth * 0.5f;

    // Just hardcode it...
    std::vector<lin_alg::vec3> vertices{
        lin_alg::vec3(-half_width, -half_height, -half_depth),
        lin_alg::vec3(-half_width, -half_height, half_depth),
        lin_alg::vec3(-half_width, half_height, -half_depth),
        lin_alg::vec3(-half_width, half_height, half_depth),
        lin_alg::vec3(half_width, half_height, half_depth),
        lin_alg::vec3(half_width, -half_height, half_depth),
        lin_alg::vec3(half_width, half_height, -half_depth),
        lin_alg::vec3(half_width, -half_height, -half_depth)};

    // NOT REAL NORMALS (JUST TO TEST)
    std::vector<lin_alg::vec3> normals{
        lin_alg::vec3(-half_width, -half_height, -half_depth),
        lin_alg::vec3(-half_width, -half_height, half_depth),
        lin_alg::vec3(-half_width, half_height, -half_depth),
        lin_alg::vec3(-half_width, half_height, half_depth),
        lin_alg::vec3(half_width, half_height, half_depth),
        lin_alg::vec3(half_width, -half_height, half_depth),
        lin_alg::vec3(half_width, half_height, -half_depth),
        lin_alg::vec3(half_width, -half_height, -half_depth)};

    // I'll just keep it in the same function since its hard-coded.
    std::vector<lin_alg::ivec3> indices{
        lin_alg::ivec3(0, 1, 3),
        lin_alg::ivec3(0, 2, 3),
        lin_alg::ivec3(4, 5, 7),
        lin_alg::ivec3(4, 6, 7),
        lin_alg::ivec3(1, 5, 0),
        lin_alg::ivec3(0, 5, 7),
        lin_alg::ivec3(0, 2, 7),
        lin_alg::ivec3(2, 6, 7),
        lin_alg::ivec3(2, 4, 6),
        lin_alg::ivec3(2, 3, 4),
        lin_alg::ivec3(1, 5, 3),
        lin_alg::ivec3(3, 5, 4)};

    std::vector<GLfloat> texture_coords = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f};

    ss::Mesh mesh;
    mesh.vertices = vertices;
    mesh.indices = indices;
    mesh.normals = normals;
    mesh.tex_coord = texture_coords;
    mesh.mat_id = mat_id;
    return mesh;
}