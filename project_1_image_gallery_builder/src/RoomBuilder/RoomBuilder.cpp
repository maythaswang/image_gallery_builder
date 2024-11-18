#include "./RoomBuilder.h"
RoomBuilder::RoomBuilder(Scene *, int x, int y)
{
    this->scene = scene;
    this->x = x;
    this->y = y;
}

void RoomBuilder::init_basic_materials()
{
    // MAT ID 0
    ss::Material floor;
    floor.ambient = lin_alg::vec3(1, 1, 1);
    floor.diffuse = lin_alg::vec3(1, 1, 1);
    floor.specular = lin_alg::vec3(1, 1, 1);
    floor.shininess = 0.7f;
    floor.texture_id = 0;

    // MAT ID 1
    ss::Material wall;
    wall.ambient = lin_alg::vec3();
    wall.diffuse = lin_alg::vec3();
    wall.specular = lin_alg::vec3();
    wall.shininess = 0.5f;
    wall.texture_id = 0;

    // MAT ID 2
    ss::Material ceiling; 
    ceiling.ambient = lin_alg::vec3(1,1,1);
    ceiling.diffuse = lin_alg::vec3(1, 1, 1);
    ceiling.specular = lin_alg::vec3(1, 1, 1);
    ceiling.shininess = 0.7f;
    ceiling.texture_id = 0;

    // MAT ID 3
    ss::Material light_emittor; 
    light_emittor.ambient = lin_alg::vec3(1,1,1);
    light_emittor.diffuse = lin_alg::vec3(1, 1, 1);
    light_emittor.specular = lin_alg::vec3(1, 1, 1);
    light_emittor.shininess = 0.7f;
    light_emittor.texture_id = 0;

    scene->add_material(floor);
    scene->add_material(wall);
    scene->add_material(ceiling);
    scene->add_material(light_emittor);

}