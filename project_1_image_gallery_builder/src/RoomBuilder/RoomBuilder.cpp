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
    floor.specular = lin_alg::vec3(1.0f, 1.0f, 1.0f);
    floor.shininess = 0.7f;
    floor.texture_id = 0;

    // MAT ID 1
    ss::Material ceiling;
    ceiling.ambient = lin_alg::vec3(0.4f, 0.4f, 0.4f);
    ceiling.diffuse = lin_alg::vec3(0.2f, 0.2f, 0.3f);
    ceiling.specular = lin_alg::vec3(0.2f, 0.2f, 0.2f);
    ceiling.shininess = 0.5f;
    ceiling.texture_id = 0;

    // MAT ID 2
    ss::Material wall;
    wall.ambient = lin_alg::vec3(0.2f, 0.3f, 0.3f);
    wall.diffuse = lin_alg::vec3(0.2f, 1.0f, 1.0f);
    wall.specular = lin_alg::vec3(1.0f, 1.0f, 1.0f);
    wall.shininess = 0.7f;
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
    lin_alg::mat4 light_t_mat = lin_alg::translate(lin_alg::vec3(0.0f, WIDTH - 0.1f / 2.0f - 0.01f, 0));
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
        point_light.position = lin_alg::vec3(lin_alg::transpose(light_t_mat) * lin_alg::vec4());
        point_light.ambient = lin_alg::vec3(1, 1, 1);
        point_light.diffuse = lin_alg::vec3(1, 1, 1);
        point_light.specular = lin_alg::vec3(1, 1, 1);
        point_light.constant = 1;
        point_light.linear = 1;
        point_light.quadratic = 1;
        this->scene->add_point_light(point_light);
    }

    // PLANES
    ss::Mesh floor = this->geometry_builder.init_plane(WIDTH, DEPTH, 0);
    ss::Mesh ceil = this->geometry_builder.init_plane(WIDTH, DEPTH, 1);

    if (has_wall_N)
    {
        ss::Mesh wall_n = this->geometry_builder.init_plane(WIDTH, DEPTH, 2);
        std::vector<lin_alg::vec3> tmp_vert;

        lin_alg::mat4 t_mat = lin_alg::translate(lin_alg::vec3(0, WIDTH / 2, DEPTH / 2));

        lin_alg::mat4 r_mat = lin_alg::rotate(lin_alg::mat4(1.0), lin_alg::radians(90), lin_alg::vec3(1, 0, 0));
        for (lin_alg::vec3 v : wall_n.vertices)
        {
            tmp_vert.push_back(lin_alg::vec3(r_mat * lin_alg::transpose(t_mat) * lin_alg::vec4(v)));
        }

        wall_n.vertices = tmp_vert;

        this->scene->add_mesh(wall_n);
    }

    if (has_wall_S)
    {
        ss::Mesh wall_s = this->geometry_builder.init_plane(WIDTH, DEPTH, 2);
        std::vector<lin_alg::vec3> tmp_vert;

        lin_alg::mat4 t_mat = lin_alg::translate(lin_alg::vec3(0, WIDTH / 2, -DEPTH / 2));

        lin_alg::mat4 r_mat = lin_alg::rotate(lin_alg::mat4(1.0), lin_alg::radians(-90), lin_alg::vec3(1, 0, 0));

        for (lin_alg::vec3 v : wall_s.vertices)
        {
            tmp_vert.push_back(lin_alg::vec3(r_mat * lin_alg::transpose(t_mat) * lin_alg::vec4(v)));
        }

        wall_s.vertices = tmp_vert;

        this->scene->add_mesh(wall_s);
    }

    if (has_wall_E)
    {
        ss::Mesh wall_e = this->geometry_builder.init_plane(WIDTH, DEPTH, 2);
        std::vector<lin_alg::vec3> tmp_vert;

        lin_alg::mat4 t_mat = lin_alg::translate(lin_alg::vec3(-WIDTH / 2, DEPTH / 2, 0));

        lin_alg::mat4 r_mat = lin_alg::rotate(lin_alg::mat4(1.0), lin_alg::radians(-90), lin_alg::vec3(0, 0, 1));
        for (lin_alg::vec3 v : wall_e.vertices)
        {
            tmp_vert.push_back(lin_alg::vec3(r_mat * lin_alg::transpose(t_mat) * lin_alg::vec4(v)));
        }

        wall_e.vertices = tmp_vert;

        this->scene->add_mesh(wall_e);
    }

    if (has_wall_W)
    {
        ss::Mesh wall_w = this->geometry_builder.init_plane(WIDTH, DEPTH, 2);
        std::vector<lin_alg::vec3> tmp_vert;

        lin_alg::mat4 t_mat = lin_alg::translate(lin_alg::vec3(WIDTH / 2, DEPTH / 2, 0));

        lin_alg::mat4 r_mat = lin_alg::rotate(lin_alg::mat4(1.0), lin_alg::radians(90), lin_alg::vec3(0, 0, 1));
        for (lin_alg::vec3 v : wall_w.vertices)
        {
            tmp_vert.push_back(lin_alg::vec3(r_mat * lin_alg::transpose(t_mat) * lin_alg::vec4(v)));
        }

        wall_w.vertices = tmp_vert;

        this->scene->add_mesh(wall_w);
    }

    std::vector<lin_alg::vec3> tmp_vert;
    lin_alg::mat4 t_mat = lin_alg::translate(lin_alg::vec3(0, DEPTH, 0));

    lin_alg::mat4 r_mat = lin_alg::rotate(lin_alg::mat4(1.0), lin_alg::radians(180), lin_alg::vec3(0, 0, 1));
    for (lin_alg::vec3 v : ceil.vertices)
    {
        tmp_vert.push_back(lin_alg::vec3(r_mat * lin_alg::transpose(t_mat) * lin_alg::vec4(v)));
    }

    ceil.vertices = tmp_vert;

    this->scene->add_mesh(floor);
    this->scene->add_mesh(ceil);
}