#include "./RoomBuilder.h"
const float WIDTH = 2;
const float DEPTH = 2;

RoomBuilder::RoomBuilder(Scene *scene, int x, int y)
{
    this->scene = scene;
    this->x = x;
    this->y = y;
    // this->material_count = 0;
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
    ceiling.ambient = lin_alg::vec3(0.2f, 0.2f, 0.3f);
    ceiling.diffuse = lin_alg::vec3(0.35f, 0.3f, 0.25f);
    ceiling.specular = lin_alg::vec3(0.2f, 0.2f, 0.2f);
    ceiling.shininess = 0.1f;
    ceiling.texture_id = 0;

    // MAT ID 2
    ss::Material wall;
    wall.ambient = lin_alg::vec3(0.2f, 0.25f, 0.3f);
    wall.diffuse = lin_alg::vec3(0.2f, 0.3, 0.3f);
    wall.specular = lin_alg::vec3(0.2f, 0.1f, 0.1f);
    wall.shininess = 0.1f;
    wall.texture_id = 0;

    // MAT ID 3
    ss::Material lamp_off;
    lamp_off.ambient = lin_alg::vec3(0.2f, 0.2f, 0.3f);
    lamp_off.diffuse = lin_alg::vec3(0.2f, 0.2f, 0.3f);
    lamp_off.specular = lin_alg::vec3(0.2f, 0.2f, 0.2f);
    lamp_off.shininess = 0.7f;
    lamp_off.texture_id = 0;

    // MAT ID 4
    ss::Material lamp_on;
    lamp_on.ambient = lin_alg::vec3(1, 1, 1);
    lamp_on.diffuse = lin_alg::vec3(1, 1, 1);
    lamp_on.specular = lin_alg::vec3(1, 1, 1);
    lamp_on.shininess = 0.7f;
    lamp_on.texture_id = 0;

    // MAT ID 5
    ss::Material canvas_frame;
    canvas_frame.ambient = lin_alg::vec3(1, 1, 1);
    canvas_frame.diffuse = lin_alg::vec3(1, 1, 1);
    canvas_frame.specular = lin_alg::vec3(1, 1, 1);
    canvas_frame.shininess = 0.7f;
    canvas_frame.texture_id = 0;

    this->scene->add_material(floor);
    this->scene->add_material(ceiling);
    this->scene->add_material(wall);
    this->scene->add_material(lamp_off);
    this->scene->add_material(lamp_on);
    this->scene->add_material(canvas_frame);

    // this->material_count += 6;
}

/**
 * @brief RIGHT NOW THIS IS UNCLEANED AND IS VERY DIRTY
 * TODO: CLEAN THIS
 */
void RoomBuilder::build_room(int row, int col, bool light_on, bool has_wall_N, bool has_wall_S, bool has_wall_E, bool has_wall_W, std::string wall_image_N, std::string wall_image_S, std::string wall_image_E, std::string wall_image_W)
{
    if (row > this->x || col > this->y || row < 0 || col < 0)
    {
        std::cout << "Invalid Room [row,col]" << '\n';
        return;
    }
    ss::Mesh lamp;
    std::vector<lin_alg::vec3> light_tmp_vert;

    float lamp_mat = 3 + light_on;

    // Lamp

    // Add lighting
    if (light_on)
    {
        lamp = this->geometry_builder.init_box_flipped(0.5, 0.1, 0.5, lamp_mat);
        ss::PointLight point_light;
        point_light.position = lin_alg::vec3(row * WIDTH, WIDTH - 0.05, col * DEPTH);
        point_light.ambient = lin_alg::vec3(0.3, 0.3, 0.3);
        point_light.diffuse = lin_alg::vec3(0.5, 0.45, 0.3);
        point_light.specular = lin_alg::vec3(0.2, 0.2, 0.2);
        point_light.constant = 0;
        point_light.linear = 0.8;
        point_light.quadratic = 0;
        this->scene->add_point_light(point_light);
    }
    else
    {
        lamp = this->geometry_builder.init_box(0.5, 0.1, 0.5, lamp_mat);
    }

    this->transform_plane(&lamp, row, col, lin_alg::vec3(0.0f, WIDTH - 0.05f, 0.0f), 0, lin_alg::vec3());
    this->scene->add_mesh(lamp);

    std::cout << "lamp: " << lamp.mat_id << '\n';

    // PLANES
    ss::Mesh floor = this->geometry_builder.init_plane(WIDTH, DEPTH, 0);
    this->transform_plane(&floor, row, col, lin_alg::vec3(0, 0, 0), 0.0f, lin_alg::vec3(0, 0, 0));
    this->scene->add_mesh(floor);

    ss::Mesh ceil = this->geometry_builder.init_plane(WIDTH, DEPTH, 1);
    this->transform_plane(&ceil, row, col, lin_alg::vec3(0, DEPTH, 0), -180.0f, lin_alg::vec3(1, 0, 0));
    this->scene->add_mesh(ceil);

    if (has_wall_N)
    {
        lin_alg::vec3 translate_vec = lin_alg::vec3(0, WIDTH / 2, DEPTH / 2);
        GLfloat degree = 90.0f;
        lin_alg::vec3 axis_rot = lin_alg::vec3(1.0f, 0.0f, 0.0f);

        ss::Mesh wall_n = this->geometry_builder.init_plane(WIDTH, DEPTH, 2);

        this->transform_plane(&wall_n, row, col, translate_vec, degree, axis_rot);
        this->scene->add_mesh(wall_n);
        if (wall_image_N != "")
        {
            this->add_canvas(row,col,translate_vec,degree,axis_rot,wall_image_N);
        }
    }

    if (has_wall_S)
    {
        lin_alg::vec3 translate_vec = lin_alg::vec3(0, WIDTH / 2, -DEPTH / 2);
        GLfloat degree = -90.0f;
        lin_alg::vec3 axis_rot = lin_alg::vec3(1.0f, 0.0f, 0.0f);

        ss::Mesh wall_s = this->geometry_builder.init_plane(WIDTH, DEPTH, 2);
        this->transform_plane(&wall_s, row, col, translate_vec, degree, axis_rot);
        this->scene->add_mesh(wall_s);
        if (wall_image_S != "")
        {
            this->add_canvas(row,col,translate_vec,degree,axis_rot,wall_image_S);
        }
    }

    if (has_wall_E)
    {
        ss::Mesh wall_e = this->geometry_builder.init_plane(WIDTH, DEPTH, 2);
        this->transform_plane(&wall_e, row, col, lin_alg::vec3(-WIDTH / 2, DEPTH / 2, 0), 90.0f, lin_alg::vec3(0.0f, 0.0f, 1.0f));
        this->scene->add_mesh(wall_e);
    }

    if (has_wall_W)
    {
        ss::Mesh wall_w = this->geometry_builder.init_plane(WIDTH, DEPTH, 2);
        this->transform_plane(&wall_w, row, col, lin_alg::vec3(WIDTH / 2, DEPTH / 2, 0), -90.0f, lin_alg::vec3(0.0f, 0.0f, 1.0f));
        this->scene->add_mesh(wall_w);
    }
}

void RoomBuilder::transform_plane(ss::Mesh *mesh, int row, int col, lin_alg::vec3 translate_vec, GLfloat degree, lin_alg::vec3 axis_rot)
{
    std::vector<lin_alg::vec3> tmp_vert;
    std::vector<lin_alg::vec3> tmp_norm;

    lin_alg::mat4 t_room = lin_alg::translate(lin_alg::vec3(row * WIDTH, 0, col * DEPTH));

    lin_alg::mat4 t_mat = lin_alg::translate(translate_vec);

    lin_alg::mat4 r_mat = lin_alg::rotate(lin_alg::mat4(1.0), lin_alg::radians(degree), axis_rot);
    for (int i = 0; i < mesh->vertices.size(); i++)
    {
        tmp_vert.push_back(lin_alg::vec3(r_mat * lin_alg::transpose(t_mat) * lin_alg::transpose(t_room) * lin_alg::vec4(mesh->vertices[i])));
        tmp_norm.push_back(lin_alg::vec3(r_mat * lin_alg::vec4(mesh->normals[i])));
    }

    mesh->vertices = tmp_vert;
    mesh->normals = tmp_norm;
}

int RoomBuilder::create_canvas_material(std::string texture_path, GLfloat &canvas_width, GLfloat &canvas_height)
{
    // Poll material limit for the sceen, if
    ss::Material canvas_image;

    // We set the id to the latest one that is unused
    int mat_id = this->scene->get_material_count();

    // add new texture
    int tex_valid = this->scene->add_texture(texture_path, 0, GL_RGB, GL_RGB);
    int tex_id = 32;

    GLfloat width = 0.5;
    GLfloat height = 0.5;
    if (tex_valid)
    {
        tex_id = this->scene->get_texture_count()-1;
        this->scene->get_texture_data(tex_id, width, height);

        int total = (width + height);
        width/=total; 
        height/= total;

    }
    // Set material information
    canvas_image.ambient = lin_alg::vec3(1, 1, 1);
    canvas_image.diffuse = lin_alg::vec3(1, 1, 1);
    canvas_image.specular = lin_alg::vec3(0.2, 0.2, 0.2);
    canvas_image.shininess = 0.7f;
    canvas_image.texture_id = tex_id; // basically send it to the void if the tex_id is weird

    // add new material
    this->scene->add_material(canvas_image);

    canvas_width = width * WIDTH;
    canvas_height = height * DEPTH;

    return mat_id;
}

void RoomBuilder::add_canvas(int row, int col, lin_alg::vec3 translate_vec, GLfloat degree, lin_alg::vec3 axis_rot, std::string image_path)
{
    ss::Mesh image_frame_n = this->geometry_builder.init_canvas_frame(WIDTH / 2, DEPTH / 2, 5);
    this->transform_plane(&image_frame_n, 0, 0, lin_alg::vec3(0, 0.05, 0), 0, lin_alg::vec3());
    this->transform_plane(&image_frame_n, row, col, translate_vec, degree, axis_rot);
    this->scene->add_mesh(image_frame_n);

    // Create material for canvas image
    GLfloat canvas_width, canvas_height;
    int mat_id = this->create_canvas_material(image_path, canvas_width, canvas_height);
    ss::Mesh canvas_image_n = this->geometry_builder.init_plane(canvas_width, canvas_height, mat_id);

    this->transform_plane(&canvas_image_n, 0, 0, lin_alg::vec3(0, 0.1, 0), 0, lin_alg::vec3());
    this->transform_plane(&canvas_image_n, row, col, translate_vec, degree, axis_rot);
    this->scene->add_mesh(canvas_image_n);
    // std::cout << mat_id << '\n';
}