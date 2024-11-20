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
        lin_alg::vec3(0, 1, 0),
        lin_alg::vec3(0, 1, 0),
        lin_alg::vec3(0, 1, 0),
        lin_alg::vec3(0, 1, 0)};

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

ss::Mesh GeometryBuilder::init_canvas_frame(GLfloat width, GLfloat depth, GLuint mat_id)
{
    const GLuint n_vert = 16;
    const GLuint n_inds = 8;

    GLfloat half_width = width * 0.5f;
    GLfloat half_height = 0.05;
    GLfloat half_depth = depth * 0.5f;

    std::vector<lin_alg::vec3> vertices{
        // // Bottom face
        // lin_alg::vec3(-half_width, -half_height, -half_depth),
        // lin_alg::vec3(-half_width, -half_height, half_depth),
        // lin_alg::vec3(half_width, -half_height, half_depth),
        // lin_alg::vec3(half_width, -half_height, -half_depth),

        // // Top face
        // lin_alg::vec3(-half_width, half_height, -half_depth),
        // lin_alg::vec3(-half_width, half_height, half_depth),
        // lin_alg::vec3(half_width, half_height, half_depth),
        // lin_alg::vec3(half_width, half_height, -half_depth),

        // Front face
        lin_alg::vec3(-half_width, -half_height, half_depth),
        lin_alg::vec3(-half_width, half_height, half_depth),
        lin_alg::vec3(half_width, half_height, half_depth),
        lin_alg::vec3(half_width, -half_height, half_depth),

        // Back face
        lin_alg::vec3(-half_width, -half_height, -half_depth),
        lin_alg::vec3(-half_width, half_height, -half_depth),
        lin_alg::vec3(half_width, half_height, -half_depth),
        lin_alg::vec3(half_width, -half_height, -half_depth),

        // Left face
        lin_alg::vec3(-half_width, -half_height, -half_depth),
        lin_alg::vec3(-half_width, -half_height, half_depth),
        lin_alg::vec3(-half_width, half_height, half_depth),
        lin_alg::vec3(-half_width, half_height, -half_depth),

        // Right face
        lin_alg::vec3(half_width, -half_height, -half_depth),
        lin_alg::vec3(half_width, -half_height, half_depth),
        lin_alg::vec3(half_width, half_height, half_depth),
        lin_alg::vec3(half_width, half_height, -half_depth),
    };

    std::vector<lin_alg::vec3> normals{
        // // Bottom face
        // lin_alg::vec3(0.0f, 1.0f, 0.0f),
        // lin_alg::vec3(0.0f, 1.0f, 0.0f),
        // lin_alg::vec3(0.0f, 1.0f, 0.0f),
        // lin_alg::vec3(0.0f, 1.0f, 0.0f),

        // // Top face
        // lin_alg::vec3(0.0f, -1.0f, 0.0f),
        // lin_alg::vec3(0.0f, -1.0f, 0.0f),
        // lin_alg::vec3(0.0f, -1.0f, 0.0f),
        // lin_alg::vec3(0.0f, -1.0f, 0.0f),

        // Front face
        lin_alg::vec3(0.0f, 0.0f, 1.0f),
        lin_alg::vec3(0.0f, 0.0f, 1.0f),
        lin_alg::vec3(0.0f, 0.0f, 1.0f),
        lin_alg::vec3(0.0f, 0.0f, 1.0f),

        // Back face
        lin_alg::vec3(0.0f, 0.0f, -1.0f),
        lin_alg::vec3(0.0f, 0.0f, -1.0f),
        lin_alg::vec3(0.0f, 0.0f, -1.0f),
        lin_alg::vec3(0.0f, 0.0f, -1.0f),

        // Left face
        lin_alg::vec3(-1.0f, 0.0f, 0.0f),
        lin_alg::vec3(-1.0f, 0.0f, 0.0f),
        lin_alg::vec3(-1.0f, 0.0f, 0.0f),
        lin_alg::vec3(-1.0f, 0.0f, 0.0f),

        // Right face
        lin_alg::vec3(1.0f, 0.0f, 0.0f),
        lin_alg::vec3(1.0f, 0.0f, 0.0f),
        lin_alg::vec3(1.0f, 0.0f, 0.0f),
        lin_alg::vec3(1.0f, 0.0f, 0.0f),
    };

    std::vector<lin_alg::ivec3> indices{
        lin_alg::ivec3(0, 1, 2),
        lin_alg::ivec3(0, 2, 3),
        lin_alg::ivec3(4, 5, 6),
        lin_alg::ivec3(4, 6, 7),
        lin_alg::ivec3(8, 9, 10),
        lin_alg::ivec3(8, 10, 11),
        lin_alg::ivec3(12, 13, 14),
        lin_alg::ivec3(12, 14, 15)};

    // Texture coordinates (mapping for each face)
    std::vector<GLfloat> texture_coords = {
        // // Bottom face
        // 0.0f,
        // 0.0f,
        // 1.0f,
        // 0.0f,
        // 1.0f,
        // 1.0f,
        // 0.0f,
        // 1.0f,

        // // Top face
        // 0.0f,
        // 0.0f,
        // 1.0f,
        // 0.0f,
        // 1.0f,
        // 1.0f,
        // 0.0f,
        // 1.0f,

        // Front face
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
        1.0f,

        // Back face
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
        1.0f,

        // Left face
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
        1.0f,

        // Right face
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
        1.0f,
    };

    // Create the mesh and assign the data
    ss::Mesh mesh;
    mesh.vertices = vertices;
    mesh.indices = indices;
    mesh.normals = normals;
    mesh.tex_coord = texture_coords;
    mesh.mat_id = mat_id;

    return mesh;
}

// Make a non-flipped normal version of this.
ss::Mesh GeometryBuilder::init_box(GLfloat width, GLfloat height, GLfloat depth, GLfloat mat_id)
{
    const GLuint n_vert = 24;
    const GLuint n_inds = 12;

    GLfloat half_width = width * 0.5f;
    GLfloat half_height = height * 0.5f;
    GLfloat half_depth = depth * 0.5f;

    std::vector<lin_alg::vec3> vertices{
        // Bottom face
        lin_alg::vec3(-half_width, -half_height, -half_depth),
        lin_alg::vec3(-half_width, -half_height, half_depth),
        lin_alg::vec3(half_width, -half_height, half_depth),
        lin_alg::vec3(half_width, -half_height, -half_depth),

        // Top face
        lin_alg::vec3(-half_width, half_height, -half_depth),
        lin_alg::vec3(-half_width, half_height, half_depth),
        lin_alg::vec3(half_width, half_height, half_depth),
        lin_alg::vec3(half_width, half_height, -half_depth),

        // Front face
        lin_alg::vec3(-half_width, -half_height, half_depth),
        lin_alg::vec3(-half_width, half_height, half_depth),
        lin_alg::vec3(half_width, half_height, half_depth),
        lin_alg::vec3(half_width, -half_height, half_depth),

        // Back face
        lin_alg::vec3(-half_width, -half_height, -half_depth),
        lin_alg::vec3(-half_width, half_height, -half_depth),
        lin_alg::vec3(half_width, half_height, -half_depth),
        lin_alg::vec3(half_width, -half_height, -half_depth),

        // Left face
        lin_alg::vec3(-half_width, -half_height, -half_depth),
        lin_alg::vec3(-half_width, -half_height, half_depth),
        lin_alg::vec3(-half_width, half_height, half_depth),
        lin_alg::vec3(-half_width, half_height, -half_depth),

        // Right face
        lin_alg::vec3(half_width, -half_height, -half_depth),
        lin_alg::vec3(half_width, -half_height, half_depth),
        lin_alg::vec3(half_width, half_height, half_depth),
        lin_alg::vec3(half_width, half_height, -half_depth),
    };

    std::vector<lin_alg::vec3> normals{
        // Bottom face
        lin_alg::vec3(0.0f, 1.0f, 0.0f),
        lin_alg::vec3(0.0f, 1.0f, 0.0f),
        lin_alg::vec3(0.0f, 1.0f, 0.0f),
        lin_alg::vec3(0.0f, 1.0f, 0.0f),

        // Top face
        lin_alg::vec3(0.0f, -1.0f, 0.0f),
        lin_alg::vec3(0.0f, -1.0f, 0.0f),
        lin_alg::vec3(0.0f, -1.0f, 0.0f),
        lin_alg::vec3(0.0f, -1.0f, 0.0f),

        // Front face
        lin_alg::vec3(0.0f, 0.0f, 1.0f),
        lin_alg::vec3(0.0f, 0.0f, 1.0f),
        lin_alg::vec3(0.0f, 0.0f, 1.0f),
        lin_alg::vec3(0.0f, 0.0f, 1.0f),

        // Back face
        lin_alg::vec3(0.0f, 0.0f, -1.0f),
        lin_alg::vec3(0.0f, 0.0f, -1.0f),
        lin_alg::vec3(0.0f, 0.0f, -1.0f),
        lin_alg::vec3(0.0f, 0.0f, -1.0f),

        // Left face
        lin_alg::vec3(-1.0f, 0.0f, 0.0f),
        lin_alg::vec3(-1.0f, 0.0f, 0.0f),
        lin_alg::vec3(-1.0f, 0.0f, 0.0f),
        lin_alg::vec3(-1.0f, 0.0f, 0.0f),

        // Right face
        lin_alg::vec3(1.0f, 0.0f, 0.0f),
        lin_alg::vec3(1.0f, 0.0f, 0.0f),
        lin_alg::vec3(1.0f, 0.0f, 0.0f),
        lin_alg::vec3(1.0f, 0.0f, 0.0f),
    };

    std::vector<lin_alg::ivec3> indices{
        lin_alg::ivec3(0, 1, 2),
        lin_alg::ivec3(0, 2, 3),
        lin_alg::ivec3(4, 5, 6),
        lin_alg::ivec3(4, 6, 7),
        lin_alg::ivec3(8, 9, 10),
        lin_alg::ivec3(8, 10, 11),
        lin_alg::ivec3(12, 13, 14),
        lin_alg::ivec3(12, 14, 15),
        lin_alg::ivec3(16, 17, 18),
        lin_alg::ivec3(16, 18, 19),
        lin_alg::ivec3(20, 21, 22),
        lin_alg::ivec3(20, 22, 23),
    };

    // Texture coordinates (mapping for each face)
    std::vector<GLfloat> texture_coords = {
        // Bottom face
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
        1.0f,

        // Top face
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
        1.0f,

        // Front face
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
        1.0f,

        // Back face
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
        1.0f,

        // Left face
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
        1.0f,

        // Right face
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
        1.0f,
    };

    // Create the mesh and assign the data
    ss::Mesh mesh;
    mesh.vertices = vertices;
    mesh.indices = indices;
    mesh.normals = normals;
    mesh.tex_coord = texture_coords;
    mesh.mat_id = mat_id;

    return mesh;
}

ss::Mesh GeometryBuilder::init_box_flipped(GLfloat width, GLfloat height, GLfloat depth, GLfloat mat_id)
{
    const GLuint n_vert = 24;
    const GLuint n_inds = 12;

    GLfloat half_width = width * 0.5f;
    GLfloat half_height = height * 0.5f;
    GLfloat half_depth = depth * 0.5f;

    std::vector<lin_alg::vec3> vertices{
        // Bottom face
        lin_alg::vec3(-half_width, -half_height, -half_depth),
        lin_alg::vec3(-half_width, -half_height, half_depth),
        lin_alg::vec3(half_width, -half_height, half_depth),
        lin_alg::vec3(half_width, -half_height, -half_depth),

        // Top face
        lin_alg::vec3(-half_width, half_height, -half_depth),
        lin_alg::vec3(-half_width, half_height, half_depth),
        lin_alg::vec3(half_width, half_height, half_depth),
        lin_alg::vec3(half_width, half_height, -half_depth),

        // Front face
        lin_alg::vec3(-half_width, -half_height, half_depth),
        lin_alg::vec3(-half_width, half_height, half_depth),
        lin_alg::vec3(half_width, half_height, half_depth),
        lin_alg::vec3(half_width, -half_height, half_depth),

        // Back face
        lin_alg::vec3(-half_width, -half_height, -half_depth),
        lin_alg::vec3(-half_width, half_height, -half_depth),
        lin_alg::vec3(half_width, half_height, -half_depth),
        lin_alg::vec3(half_width, -half_height, -half_depth),

        // Left face
        lin_alg::vec3(-half_width, -half_height, -half_depth),
        lin_alg::vec3(-half_width, -half_height, half_depth),
        lin_alg::vec3(-half_width, half_height, half_depth),
        lin_alg::vec3(-half_width, half_height, -half_depth),

        // Right face
        lin_alg::vec3(half_width, -half_height, -half_depth),
        lin_alg::vec3(half_width, -half_height, half_depth),
        lin_alg::vec3(half_width, half_height, half_depth),
        lin_alg::vec3(half_width, half_height, -half_depth),
    };

    std::vector<lin_alg::vec3> normals{
        // Bottom face
        lin_alg::vec3(0.0f, 1.0f, 0.0f),
        lin_alg::vec3(0.0f, 1.0f, 0.0f),
        lin_alg::vec3(0.0f, 1.0f, 0.0f),
        lin_alg::vec3(0.0f, 1.0f, 0.0f),

        // Top face
        lin_alg::vec3(0.0f, -1.0f, 0.0f),
        lin_alg::vec3(0.0f, -1.0f, 0.0f),
        lin_alg::vec3(0.0f, -1.0f, 0.0f),
        lin_alg::vec3(0.0f, -1.0f, 0.0f),

        // Front face
        lin_alg::vec3(0.0f, 0.0f, -1.0f),
        lin_alg::vec3(0.0f, 0.0f, -1.0f),
        lin_alg::vec3(0.0f, 0.0f, -1.0f),
        lin_alg::vec3(0.0f, 0.0f, -1.0f),

        // Back face
        lin_alg::vec3(0.0f, 0.0f, 1.0f),
        lin_alg::vec3(0.0f, 0.0f, 1.0f),
        lin_alg::vec3(0.0f, 0.0f, 1.0f),
        lin_alg::vec3(0.0f, 0.0f, 1.0f),

        // Left face
        lin_alg::vec3(1.0f, 0.0f, 0.0f),
        lin_alg::vec3(1.0f, 0.0f, 0.0f),
        lin_alg::vec3(1.0f, 0.0f, 0.0f),
        lin_alg::vec3(1.0f, 0.0f, 0.0f),

        // Right face
        lin_alg::vec3(-1.0f, 0.0f, 0.0f),
        lin_alg::vec3(-1.0f, 0.0f, 0.0f),
        lin_alg::vec3(-1.0f, 0.0f, 0.0f),
        lin_alg::vec3(-1.0f, 0.0f, 0.0f),
    };

    std::vector<lin_alg::ivec3> indices{
        lin_alg::ivec3(0, 1, 2),
        lin_alg::ivec3(0, 2, 3),
        lin_alg::ivec3(4, 5, 6),
        lin_alg::ivec3(4, 6, 7),
        lin_alg::ivec3(8, 9, 10),
        lin_alg::ivec3(8, 10, 11),
        lin_alg::ivec3(12, 13, 14),
        lin_alg::ivec3(12, 14, 15),
        lin_alg::ivec3(16, 17, 18),
        lin_alg::ivec3(16, 18, 19),
        lin_alg::ivec3(20, 21, 22),
        lin_alg::ivec3(20, 22, 23),
    };

    // Texture coordinates (mapping for each face)
    std::vector<GLfloat> texture_coords = {
        // Bottom face
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
        1.0f,

        // Top face
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
        1.0f,

        // Front face
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
        1.0f,

        // Back face
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
        1.0f,

        // Left face
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
        1.0f,

        // Right face
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
        1.0f,
    };

    // Create the mesh and assign the data
    ss::Mesh mesh;
    mesh.vertices = vertices;
    mesh.indices = indices;
    mesh.normals = normals;
    mesh.tex_coord = texture_coords;
    mesh.mat_id = mat_id;

    return mesh;
}