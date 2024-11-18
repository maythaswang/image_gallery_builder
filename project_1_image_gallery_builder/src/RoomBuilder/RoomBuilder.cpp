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
    floor.ambient = lin_alg::vec3(1.0f, 1.0f, 1.0f);
    floor.diffuse = lin_alg::vec3(1.0f, 1.0f, 1.0f);
    floor.specular = lin_alg::vec3(1.0f, 1.0f, 1.0f);
    floor.shininess = 0.7f;
    floor.texture_id = 0;

    // MAT ID 1
    ss::Material ceiling;
    ceiling.ambient = lin_alg::vec3(1.0f, 0.3f, 0.2f);
    ceiling.diffuse = lin_alg::vec3(1.0f, 0.4f, 0.3f);
    ceiling.specular = lin_alg::vec3(0.2f, 0.2f, 0.2f);
    ceiling.shininess = 0.5f;
    ceiling.texture_id = 0;

    // MAT ID 2
    ss::Material wall;
    wall.ambient = lin_alg::vec3(1.0f, 0.4f, 1.0f);
    wall.diffuse = lin_alg::vec3(0.2f, 1.0f, 1.0f);
    wall.specular = lin_alg::vec3(1.0f, 1.0f, 1.0f);
    wall.shininess = 0.7f;
    wall.texture_id = 0;

    // MAT ID 3
    ss::Material light_emittor;
    light_emittor.ambient = lin_alg::vec3(1, 1, 1);
    light_emittor.diffuse = lin_alg::vec3(1, 1, 1);
    light_emittor.specular = lin_alg::vec3(1, 1, 1);
    light_emittor.shininess = 0.7f;
    light_emittor.texture_id = 0;

    this->scene->add_material(floor);
    this->scene->add_material(wall);
    this->scene->add_material(ceiling);
    this->scene->add_material(light_emittor);
}

void RoomBuilder::build_room(int row, int col, bool light_on, bool has_wall_N, bool has_wall_S, bool has_wall_E, bool has_wall_W, std::string wall_image_N, std::string wall_image_S, std::string wall_image_E, std::string wall_image_W)
{
    if (row > 5 || col > 5 || row < 0 || col << 0)
    {
        std::cout << "Invalid Room [row,col]" << '\n';
        return;
    }

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

        // for (int i = 0; i < 4; i++)
        // {
        //     for (int j = 0; j < 4; j++)
        //     {
        //         std::cout << (t_mat * r_mat)[i][j] << ' ';
        //     }
        //     std::cout << '\n';
        // }

        // for (int i = 0; i < 4; i++)
        // {
        //     std::cout << lin_alg::vec4(wall_s.vertices[0])[i] << ' ';
        // }
        // for (int i = 0; i < 4; i++)
        // {
        //     std::cout << lin_alg::vec4(wall_s.vertices[1])[i] << ' ';
        // }

        // std::cout << '\n';

        // for (int i = 0; i < 4; i++)
        // {
        //     std::cout << (r_mat * lin_alg::transpose(t_mat) * lin_alg::vec4(wall_s.vertices[0]))[i] << ' ';
        // }
        // for (int i = 0; i < 4; i++)

        // {
        //     std::cout << (r_mat * lin_alg::transpose(t_mat) * lin_alg::vec4(wall_s.vertices[1]))[i] << ' ';
        // }

        // std::cout << '\n';

        for (lin_alg::vec3 v : wall_s.vertices)
        {
            tmp_vert.push_back(lin_alg::vec3(r_mat * lin_alg::transpose(t_mat) * lin_alg::vec4(v)));
        }

        wall_s.vertices = tmp_vert;

        this->scene->add_mesh(wall_s);

        // wall_s.vertices = lin_alg::vec3(lin_alg::rotate(lin_alg::mat4(1.0), lin_alg::radians(90), lin_alg::vec3(0, 1, 0)) * lin_alg::vec4(wall_s.vertices));
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