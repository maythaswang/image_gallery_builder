#include "./RoomBuilder.h"
const float WIDTH = 2;
const float DEPTH = 2;

RoomBuilder::RoomBuilder(Scene *scene, int x, int y)
{
    this->scene = scene;
    this->x = x;
    this->y = y;
}

void RoomBuilder::init_basic_materials()
{
    // MAT ID 0
    ss::Material floor;
    floor.ambient = lin_alg::vec3(0.2f, 0.2f, 0.3f);
    floor.diffuse = lin_alg::vec3(1.0f, 1.0f, 1.0f);
    floor.specular = lin_alg::vec3(0.1f, 0.1f, 0.1f);
    floor.shininess = 0.05f;
    floor.texture_id = 0;

    // MAT ID 1
    ss::Material ceiling;
    ceiling.ambient = lin_alg::vec3(0.4f, 0.4f, 0.4f);
    ceiling.diffuse = lin_alg::vec3(0.2f, 0.2f, 0.3f);
    ceiling.specular = lin_alg::vec3(0.2f, 0.2f, 0.2f);
    ceiling.shininess = 0.1f;
    ceiling.texture_id = 0;

    // MAT ID 2
    ss::Material wall;
    wall.ambient = lin_alg::vec3(0.2f, 0.3f, 0.3f);
    wall.diffuse = lin_alg::vec3(0.2f, 0.4f, 0.2f);
    wall.specular = lin_alg::vec3(0.2f, 0.1f, 0.1f);
    wall.shininess = 0.1f;
    wall.texture_id = 0;

    // MAT ID 3
    ss::Material lamp_off;
    lamp_off.ambient = lin_alg::vec3(0.1f, 0.1f, 0.4f);
    lamp_off.diffuse = lin_alg::vec3(1, 1, 1);
    lamp_off.specular = lin_alg::vec3(1, 1, 1);
    lamp_off.shininess = 0.7f;
    lamp_off.texture_id = 0;

    // MAT ID 4
    ss::Material lamp_on;
    lamp_on.ambient = lin_alg::vec3(1, 1, 1);
    lamp_on.diffuse = lin_alg::vec3(1, 1, 1);
    lamp_on.specular = lin_alg::vec3(1, 1, 1);
    lamp_on.shininess = 0.7f;
    lamp_on.texture_id = 0;

    this->scene->add_material(floor);
    this->scene->add_material(ceiling);
    this->scene->add_material(wall);
    this->scene->add_material(lamp_off);
    this->scene->add_material(lamp_on);
}

// TODO: Maybe will need emittor type mesh

/**
 * @brief RIGHT NOW THIS IS UNCLEANED AND IS VERY DIRTY ALSO NONE OF THE ITEMS HERE HAVE THEIR NORMALS IN PROPER PLACE YET
 * TODO: CLEAN THIS
 * TODO: CLEAN THIS
 * TODO: CLEAN THIS
 *
 * @param row
 * @param col
 * @param light_on
 * @param has_wall_N
 * @param has_wall_S
 * @param has_wall_E
 * @param has_wall_W
 * @param wall_image_N
 * @param wall_image_S
 * @param wall_image_E
 * @param wall_image_W
 */
void RoomBuilder::build_room(int row, int col, bool light_on, bool has_wall_N, bool has_wall_S, bool has_wall_E, bool has_wall_W, std::string wall_image_N, std::string wall_image_S, std::string wall_image_E, std::string wall_image_W)
{
    if (row > this->x || col > this->y || row < 0 || col << 0)
    {
        std::cout << "Invalid Room [row,col]" << '\n';
        return;
    }
    ss::Mesh lamp;
    std::vector<lin_alg::vec3> light_tmp_vert;

    float lamp_mat = 3 + light_on;

    // Lamp
    lamp = this->geometry_builder.init_box(0.5, 0.1, 0.5, lamp_mat);
    lin_alg::mat4 light_t_mat = lin_alg::translate(lin_alg::vec3(0.0f, WIDTH - 0.1, 0));
    for (lin_alg::vec3 v : lamp.vertices)
    {
        light_tmp_vert.push_back(lin_alg::vec3(lin_alg::transpose(light_t_mat) * lin_alg::vec4(v)));
    }

    lamp.vertices = light_tmp_vert;

    this->scene->add_mesh(lamp);

    // Add lighting
    if (light_on)
    {
        ss::PointLight point_light;
        point_light.position = lin_alg::vec3(0,WIDTH - 0.09,0);
        point_light.ambient = lin_alg::vec3(0.1, 0.1, 0.1);
        point_light.diffuse = lin_alg::vec3(0.5, 0.45, 0.3);
        point_light.specular = lin_alg::vec3(0.2, 0.3, 0.2);
        point_light.constant = 0;
        point_light.linear = 0.7;
        point_light.quadratic = 0;
        this->scene->add_point_light(point_light);
    }

    // PLANES
    ss::Mesh floor = this->geometry_builder.init_plane(WIDTH, DEPTH, 0);
    ss::Mesh ceil = this->geometry_builder.init_plane(WIDTH, DEPTH, 1);

    // std::cout << ceil.normals[0].x << ' ' << ceil.normals[0].y << ' ' << ceil.normals[0].z << '\n';
    this->transform_plane(&ceil, lin_alg::vec3(0, DEPTH, 0), -180.0f, lin_alg::vec3(1, 0, 0));
    // std::cout << ceil.normals[0].x << ' ' << ceil.normals[0].y << ' ' << ceil.normals[0].z << '\n';

    if (has_wall_N)
    {
        ss::Mesh wall_n = this->geometry_builder.init_plane(WIDTH, DEPTH, 2);
        std::cout << wall_n.normals[0].x << ' ' << wall_n.normals[0].y << ' ' << wall_n.normals[0].z << '\n';
        this->transform_plane(&wall_n, lin_alg::vec3(0, WIDTH / 2, DEPTH / 2), 90.0f, lin_alg::vec3(1.0f, 0.0f, 0.0f));
        std::cout << wall_n.normals[0].x << ' ' << wall_n.normals[0].y << ' ' << wall_n.normals[0].z << '\n';
        this->scene->add_mesh(wall_n);
    }

    if (has_wall_S)
    {
        ss::Mesh wall_s = this->geometry_builder.init_plane(WIDTH, DEPTH, 2);
        this->transform_plane(&wall_s, lin_alg::vec3(0, WIDTH / 2, -DEPTH / 2), -90.0f, lin_alg::vec3(1.0f, 0.0f, 0.0f));
        this->scene->add_mesh(wall_s);
    }

    if (has_wall_E)
    {
        ss::Mesh wall_e = this->geometry_builder.init_plane(WIDTH, DEPTH, 2);
        this->transform_plane(&wall_e, lin_alg::vec3(-WIDTH / 2, DEPTH / 2, 0), 90.0f, lin_alg::vec3(0.0f, 0.0f, 1.0f));
        this->scene->add_mesh(wall_e);
    }

    if (has_wall_W)
    {
        ss::Mesh wall_w = this->geometry_builder.init_plane(WIDTH, DEPTH, 2);
        this->transform_plane(&wall_w, lin_alg::vec3(WIDTH / 2, DEPTH / 2, 0), -90.0f, lin_alg::vec3(0.0f, 0.0f, 1.0f));
        this->scene->add_mesh(wall_w);
    }
    this->scene->add_mesh(floor);
    this->scene->add_mesh(ceil);
}

void RoomBuilder::transform_plane(ss::Mesh *mesh, lin_alg::vec3 translate_vec, GLfloat degree, lin_alg::vec3 axis_rot)
{
    std::vector<lin_alg::vec3> tmp_vert;
    std::vector<lin_alg::vec3> tmp_norm;
    lin_alg::mat4 t_mat = lin_alg::translate(translate_vec);

    lin_alg::mat4 r_mat = lin_alg::rotate(lin_alg::mat4(1.0), lin_alg::radians(degree), axis_rot);
    for (int i = 0; i < mesh->vertices.size(); i++)
    {
        tmp_vert.push_back(lin_alg::vec3(r_mat * lin_alg::transpose(t_mat) * lin_alg::vec4(mesh->vertices[i])));
        tmp_norm.push_back(lin_alg::vec3(r_mat * lin_alg::vec4(mesh->normals[i])));
    }

    mesh->vertices = tmp_vert;
    mesh->normals = tmp_norm;
}