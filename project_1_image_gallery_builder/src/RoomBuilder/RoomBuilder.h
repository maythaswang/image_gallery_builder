#ifndef ROOM_BUILDER_H
#define ROOM_BUILDER_H
#pragma once
#include <simple_scene/simple_scene.h>
#include "Scene/Scene.h"
#include <vector>

class RoomBuilder
{
public:
    RoomBuilder(Scene *, int, int);
    void init_basic_materials();
    std::vector<ss::Mesh> build_room(int, int, bool, bool, bool, bool, bool, std::string, std::string, std::string, std::string);

private:
    Scene *scene;
    int x;
    int y;
};

#endif