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


ss::Mesh GeometryBuilder::init_box(GLfloat width, GLfloat height, GLfloat depth, GLfloat mat_id)
{
    const GLuint n_vert = 24;  // 6 faces * 4 vertices per face
    const GLuint n_inds = 12;  // 6 faces * 2 triangles per face

    GLfloat half_width = width * 0.5f;
    GLfloat half_height = height * 0.5f;
    GLfloat half_depth = depth * 0.5f;

    // Vertices for each face of the box
    std::vector<lin_alg::vec3> vertices{
        // Bottom face (4 vertices)
        lin_alg::vec3(-half_width, -half_height, -half_depth),
        lin_alg::vec3(-half_width, -half_height, half_depth),
        lin_alg::vec3(half_width, -half_height, half_depth),
        lin_alg::vec3(half_width, -half_height, -half_depth),

        // Top face (4 vertices)
        lin_alg::vec3(-half_width, half_height, -half_depth),
        lin_alg::vec3(-half_width, half_height, half_depth),
        lin_alg::vec3(half_width, half_height, half_depth),
        lin_alg::vec3(half_width, half_height, -half_depth),

        // Front face (4 vertices)
        lin_alg::vec3(-half_width, -half_height, half_depth),
        lin_alg::vec3(-half_width, half_height, half_depth),
        lin_alg::vec3(half_width, half_height, half_depth),
        lin_alg::vec3(half_width, -half_height, half_depth),

        // Back face (4 vertices)
        lin_alg::vec3(-half_width, -half_height, -half_depth),
        lin_alg::vec3(-half_width, half_height, -half_depth),
        lin_alg::vec3(half_width, half_height, -half_depth),
        lin_alg::vec3(half_width, -half_height, -half_depth),

        // Left face (4 vertices)
        lin_alg::vec3(-half_width, -half_height, -half_depth),
        lin_alg::vec3(-half_width, -half_height, half_depth),
        lin_alg::vec3(-half_width, half_height, half_depth),
        lin_alg::vec3(-half_width, half_height, -half_depth),

        // Right face (4 vertices)
        lin_alg::vec3(half_width, -half_height, -half_depth),
        lin_alg::vec3(half_width, -half_height, half_depth),
        lin_alg::vec3(half_width, half_height, half_depth),
        lin_alg::vec3(half_width, half_height, -half_depth),
    };

    // Normals for each face (inward-facing normals)
    std::vector<lin_alg::vec3> normals{
        // Bottom face normal
        lin_alg::vec3(0.0f, 1.0f, 0.0f),
        lin_alg::vec3(0.0f, 1.0f, 0.0f),
        lin_alg::vec3(0.0f, 1.0f, 0.0f),
        lin_alg::vec3(0.0f, 1.0f, 0.0f),

        // Top face normal
        lin_alg::vec3(0.0f, -1.0f, 0.0f),
        lin_alg::vec3(0.0f, -1.0f, 0.0f),
        lin_alg::vec3(0.0f, -1.0f, 0.0f),
        lin_alg::vec3(0.0f, -1.0f, 0.0f),

        // Front face normal
        lin_alg::vec3(0.0f, 0.0f, -1.0f),
        lin_alg::vec3(0.0f, 0.0f, -1.0f),
        lin_alg::vec3(0.0f, 0.0f, -1.0f),
        lin_alg::vec3(0.0f, 0.0f, -1.0f),

        // Back face normal
        lin_alg::vec3(0.0f, 0.0f, 1.0f),
        lin_alg::vec3(0.0f, 0.0f, 1.0f),
        lin_alg::vec3(0.0f, 0.0f, 1.0f),
        lin_alg::vec3(0.0f, 0.0f, 1.0f),

        // Left face normal
        lin_alg::vec3(1.0f, 0.0f, 0.0f),
        lin_alg::vec3(1.0f, 0.0f, 0.0f),
        lin_alg::vec3(1.0f, 0.0f, 0.0f),
        lin_alg::vec3(1.0f, 0.0f, 0.0f),

        // Right face normal
        lin_alg::vec3(-1.0f, 0.0f, 0.0f),
        lin_alg::vec3(-1.0f, 0.0f, 0.0f),
        lin_alg::vec3(-1.0f, 0.0f, 0.0f),
        lin_alg::vec3(-1.0f, 0.0f, 0.0f),
    };

    // Indices for the cube (each face has two triangles)
    std::vector<lin_alg::ivec3> indices{
        // Bottom face (2 triangles)
        lin_alg::ivec3(0, 1, 2),
        lin_alg::ivec3(0, 2, 3),

        // Top face (2 triangles)
        lin_alg::ivec3(4, 5, 6),
        lin_alg::ivec3(4, 6, 7),

        // Front face (2 triangles)
        lin_alg::ivec3(8, 9, 10),
        lin_alg::ivec3(8, 10, 11),

        // Back face (2 triangles)
        lin_alg::ivec3(12, 13, 14),
        lin_alg::ivec3(12, 14, 15),

        // Left face (2 triangles)
        lin_alg::ivec3(16, 17, 18),
        lin_alg::ivec3(16, 18, 19),

        // Right face (2 triangles)
        lin_alg::ivec3(20, 21, 22),
        lin_alg::ivec3(20, 22, 23),
    };

    // Texture coordinates (mapping for each face)
    std::vector<GLfloat> texture_coords = {
        // Bottom face
        0.0f, 0.0f,  // Bottom-left
        1.0f, 0.0f,  // Bottom-right
        1.0f, 1.0f,  // Top-right
        0.0f, 1.0f,  // Top-left

        // Top face
        0.0f, 0.0f,  // Bottom-left
        1.0f, 0.0f,  // Bottom-right
        1.0f, 1.0f,  // Top-right
        0.0f, 1.0f,  // Top-left

        // Front face
        0.0f, 0.0f,  // Bottom-left
        1.0f, 0.0f,  // Bottom-right
        1.0f, 1.0f,  // Top-right
        0.0f, 1.0f,  // Top-left

        // Back face
        0.0f, 0.0f,  // Bottom-left
        1.0f, 0.0f,  // Bottom-right
        1.0f, 1.0f,  // Top-right
        0.0f, 1.0f,  // Top-left

        // Left face
        0.0f, 0.0f,  // Bottom-left
        1.0f, 0.0f,  // Bottom-right
        1.0f, 1.0f,  // Top-right
        0.0f, 1.0f,  // Top-left

        // Right face
        0.0f, 0.0f,  // Bottom-left
        1.0f, 0.0f,  // Bottom-right
        1.0f, 1.0f,  // Top-right
        0.0f, 1.0f,  // Top-left
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



// ss::Mesh GeometryBuilder::init_box(GLfloat width, GLfloat height, GLfloat depth, GLfloat mat_id)
// {
//     const GLuint n_vert = 8;
//     const GLuint n_inds = 12;

//     GLfloat half_width = width * 0.5f;
//     GLfloat half_height = height * 0.5f;
//     GLfloat half_depth = depth * 0.5f;

//     // Just hardcode it...
//     std::vector<lin_alg::vec3> vertices{
//         lin_alg::vec3(-half_width, -half_height, -half_depth),
//         lin_alg::vec3(-half_width, -half_height, half_depth),
//         lin_alg::vec3(-half_width, half_height, -half_depth),
//         lin_alg::vec3(-half_width, half_height, half_depth),
//         lin_alg::vec3(half_width, half_height, half_depth),
//         lin_alg::vec3(half_width, -half_height, half_depth),
//         lin_alg::vec3(half_width, half_height, -half_depth),
//         lin_alg::vec3(half_width, -half_height, -half_depth)};

//     // NOT REAL NORMALS (JUST TO TEST)
//     std::vector<lin_alg::vec3> normals{
//         lin_alg::vec3(-half_width, -half_height, -half_depth),
//         lin_alg::vec3(-half_width, -half_height, half_depth),
//         lin_alg::vec3(-half_width, half_height, -half_depth),
//         lin_alg::vec3(-half_width, half_height, half_depth),
//         lin_alg::vec3(half_width, half_height, half_depth),
//         lin_alg::vec3(half_width, -half_height, half_depth),
//         lin_alg::vec3(half_width, half_height, -half_depth),
//         lin_alg::vec3(half_width, -half_height, -half_depth)};

//     // I'll just keep it in the same function since its hard-coded.
//     std::vector<lin_alg::ivec3> indices{
//         lin_alg::ivec3(0, 1, 3),
//         lin_alg::ivec3(0, 2, 3),
//         lin_alg::ivec3(4, 5, 7),
//         lin_alg::ivec3(4, 6, 7),
//         lin_alg::ivec3(1, 5, 0),
//         lin_alg::ivec3(0, 5, 7),
//         lin_alg::ivec3(0, 2, 7),
//         lin_alg::ivec3(2, 6, 7),
//         lin_alg::ivec3(2, 4, 6),
//         lin_alg::ivec3(2, 3, 4),
//         lin_alg::ivec3(1, 5, 3),
//         lin_alg::ivec3(3, 5, 4)};

//     std::vector<GLfloat> texture_coords = {
//         0.0f, 0.0f,
//         1.0f, 0.0f,
//         0.0f, 1.0f,
//         1.0f, 1.0f,
//         0.0f, 1.0f,
//         0.0f, 0.0f,
//         1.0f, 1.0f,
//         1.0f, 0.0f};

//     ss::Mesh mesh;
//     mesh.vertices = vertices;
//     mesh.indices = indices;
//     mesh.normals = normals;
//     mesh.tex_coord = texture_coords;
//     mesh.mat_id = mat_id;
//     return mesh;
// }