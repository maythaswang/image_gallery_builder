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
        lin_alg::vec3(-half_width, -half_depth, 0),
        lin_alg::vec3(-half_width, half_depth, 0),
        lin_alg::vec3(half_width, -half_depth, 0),
        lin_alg::vec3(half_width, half_depth, 0)};

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
    mesh.mat_id = material_id;
    return mesh;
}

ss::Mesh GeometryBuilder::init_box(std::vector<GLfloat> center, GLfloat height, GLfloat width, GLfloat depth)
{
    const GLuint n_vert = 8;
    const GLuint n_inds = 12;
    GLfloat x = center[0];
    GLfloat y = center[1];
    GLfloat z = center[2];

    GLfloat half_width = width * 0.5f;
    GLfloat half_height = height * 0.5f;
    GLfloat half_depth = depth * 0.5f;

    // Just hardcode it...
    std::vector<lin_alg::vec3> vertices{
        lin_alg::vec3(x - half_width, y - half_height, z - half_depth),
        lin_alg::vec3(x - half_width, y - half_height, z + half_depth),
        lin_alg::vec3(x - half_width, y + half_height, z - half_depth),
        lin_alg::vec3(x - half_width, y + half_height, z + half_depth),
        lin_alg::vec3(x + half_width, y + half_height, z + half_depth),
        lin_alg::vec3(x + half_width, y - half_height, z + half_depth),
        lin_alg::vec3(x + half_width, y + half_height, z - half_depth),
        lin_alg::vec3(x + half_width, y - half_height, z - half_depth)};

    // NOT REAL NORMALS (JUST TO TEST)
    std::vector<lin_alg::vec3> normals{
        lin_alg::vec3(x - half_width, y - half_height, z - half_depth),
        lin_alg::vec3(x - half_width, y - half_height, z + half_depth),
        lin_alg::vec3(x - half_width, y + half_height, z - half_depth),
        lin_alg::vec3(x - half_width, y + half_height, z + half_depth),
        lin_alg::vec3(x + half_width, y + half_height, z + half_depth),
        lin_alg::vec3(x + half_width, y - half_height, z + half_depth),
        lin_alg::vec3(x + half_width, y + half_height, z - half_depth),
        lin_alg::vec3(x + half_width, y - half_height, z - half_depth)};

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

    // std::vector<GLfloat> texture_ids = {
    //     1.0f,
    //     1.0f,
    //     1.0f,
    //     1.0f,
    //     1.0f,
    //     1.0f,
    //     1.0f,
    //     1.0f};

    GLfloat mat_id= 1.0f; 

    ss::Mesh mesh;
    mesh.vertices = vertices;
    mesh.indices = indices;
    mesh.normals = normals;
    mesh.tex_coord = texture_coords;
    mesh.mat_id = mat_id;
    return mesh;
}

// void GeometryBuilder::init_square_pyramid(RenderComponents *render_components, std::vector<GLfloat> center, GLfloat width)
// {
//     GLfloat x = center[0];
//     GLfloat y = center[1];
//     GLfloat z = center[2];

//     GLfloat half_width = width / 2.0f;

//     std::vector<GLfloat> vertices{
//         // Face 0
//         x + half_width, y, z + half_width,
//         x + half_width, y, z - half_width,
//         x - half_width, y, z - half_width,
//         x - half_width, y, z + half_width,

//         // Face 1
//         x + half_width, y, z + half_width,
//         x + half_width, y, z - half_width,
//         x, y + half_width, z,

//         // Face 2
//         x + half_width, y, z + half_width,
//         x - half_width, y, z + half_width,
//         x, y + half_width, z,

//         // Face 3
//         x - half_width, y, z - half_width,
//         x - half_width, y, z + half_width,
//         x, y + half_width, z,

//         // Face 4
//         x + half_width, y, z - half_width,
//         x - half_width, y, z - half_width,
//         x, y + half_width, z};

//     // I'll keep it in the same function since its hard-coded.
//     std::vector<GLuint> indices{
//         0, 1, 2,
//         0, 2, 3,
//         // FACES TRIANGLE
//         4, 5, 6,
//         7, 8, 9,
//         10, 11, 12,
//         13, 14, 15};

//     // Should duplicate vertices for better results but I am lazy
//     std::vector<GLfloat> texture_coords = {
//         // FACE 0
//         1.0f,
//         1.0f,
//         1.0f,
//         0.0f,
//         0.0f,
//         0.0f,
//         0.0f,
//         1.0f,
//         // FACE 1
//         0.0f,
//         0.0f,
//         1.0f,
//         0.0f,
//         0.5f,
//         1.0f,

//         // FACE 2
//         0.0f,
//         0.0f,
//         1.0f,
//         0.0f,
//         0.5f,
//         1.0f,
//         // FACE 3
//         0.0f,
//         0.0f,
//         1.0f,
//         0.0f,
//         0.5f,
//         1.0f,
//         // FACE 4
//         0.0f,
//         0.0f,
//         1.0f,
//         0.0f,
//         0.5f,
//         1.0f,
//     };

//     std::vector<GLfloat> texture_ids = {
//         1.0f,
//         1.0f,
//         1.0f,
//         1.0f,
//         // FACE 1
//         2.0f,
//         2.0f,
//         2.0f,
//         // FACE 2
//         3.0f,
//         3.0f,
//         3.0f,
//         // FACE 3
//         4.0f,
//         4.0f,
//         4.0f,
//         // FACE 4
//         5.0f,
//         5.0f,
//         5.0f};

//     render_components->n_vert = vertices.size();
//     render_components->n_inds = indices.size();
//     init_buf(render_components, &vertices[0], &indices[0], &texture_coords[0], &texture_ids[0]);
// }

// void GeometryBuilder::init_sphere(RenderComponents *render_components, GLfloat radius, GLuint sector_count, GLuint stack_count)
// {
//     GLfloat PI = 3.14159265;

//     GLfloat x, y, z, xy, s, t;
//     GLfloat sector_step = 2 * PI / sector_count;
//     GLfloat stack_step = PI / stack_count;
//     GLfloat sector_angle, stack_angle;

//     std::vector<GLfloat> vertices;
//     std::vector<GLfloat> texture_coords;
//     std::vector<GLfloat> texture_ids;

//     // Build vertices
//     for (int i = 0; i <= stack_count; ++i)
//     {
//         stack_angle = PI / 2 - i * stack_step; // starting from pi/2 to -pi/2
//         xy = radius * cosf(stack_angle);       // r * cos(u)
//         z = radius * sinf(stack_angle);        // r * sin(u)

//         // add (sectorCount+1) vertices per stack
//         // first and last vertices have same position
//         for (int j = 0; j <= sector_count; ++j)
//         {
//             sector_angle = j * sector_step; // starting from 0 to 2pi

//             // vertex position (x, y, z)
//             x = xy * cosf(sector_angle); // r * cos(u) * cos(v)
//             y = xy * sinf(sector_angle); // r * cos(u) * sin(v)
//             vertices.push_back(x);
//             vertices.push_back(y);
//             vertices.push_back(z);

//             // tex
//             s = (GLfloat)j / sector_count;
//             t = (GLfloat)i / stack_count;
//             texture_coords.push_back(s);
//             texture_coords.push_back(t);
//             texture_ids.push_back(2.0f);
//         }
//     }

//     std::vector<GLuint> indices = this->generate_sphere_indices(stack_count, sector_count);
//     render_components->n_inds = (GLuint) (indices.size()/3);
//     render_components->n_vert = (GLuint) (vertices.size()/3);
//     init_buf(render_components, &vertices[0], &indices[0], &texture_coords[0], &texture_ids[0]);
// }

// std::vector<GLuint> GeometryBuilder::generate_sphere_indices(GLuint stack_count, GLuint sector_count)
// {
//     // generate CCW index list of sphere triangles
//     // k1--k1+1
//     // |  / |
//     // | /  |
//     // k2--k2+1
//     std::vector<GLuint> indices;
//     int k1, k2;
//     for (int i = 0; i < stack_count; ++i)
//     {
//         k1 = i * (sector_count + 1); // beginning of current stack
//         k2 = k1 + sector_count + 1;  // beginning of next stack

//         for (int j = 0; j < sector_count; ++j, ++k1, ++k2)
//         {
//             // 2 triangles per sector excluding first and last stacks
//             // k1 => k2 => k1+1
//             if (i != 0)
//             {
//                 indices.push_back(k1);
//                 indices.push_back(k2);
//                 indices.push_back(k1 + 1);
//             }

//             // k1+1 => k2 => k2+1
//             if (i != (stack_count - 1))
//             {
//                 indices.push_back(k1 + 1);
//                 indices.push_back(k2);
//                 indices.push_back(k2 + 1);
//             }
//         }
//     }
//     return indices;
// }

// void GeometryBuilder::init_buf(RenderComponents *render_components, lin_alg::vec3 *vertices, lin_alg::ivec3 *indices, GLfloat *texture_coords, GLfloat *texture_ids)
// {
//     glGenVertexArrays(1, render_components->VAO);
//     glGenBuffers(3, render_components->VBO);
//     glGenBuffers(1, render_components->EBO);

//     glBindVertexArray(*render_components->VAO); 
//     std::cout << vertices[0][0] << '\n';

//     std::cout << texture_coords[2] << '\n';

//     glEnableVertexAttribArray(0);

//     glBindBuffer(GL_ARRAY_BUFFER, render_components->VBO[0]);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * render_components->n_vert * 3, &vertices[0][0], GL_STATIC_DRAW);
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);

//     glEnableVertexAttribArray(1);

//     glBindBuffer(GL_ARRAY_BUFFER, render_components->VBO[1]);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * render_components->n_vert * 2, &texture_coords[0], GL_STATIC_DRAW);
//     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void *)0);

//     glEnableVertexAttribArray(2);
//     glBindBuffer(GL_ARRAY_BUFFER, render_components->VBO[2]);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * render_components->n_vert * 1, &texture_ids[0], GL_STATIC_DRAW);
//     glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 1 * sizeof(GLfloat), (void *)0);

//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *render_components->EBO);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * render_components->n_inds * 3, &indices[0][0], GL_STATIC_DRAW);

//     // Unbind VAOs, VBOs, EBOs
//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);
// }