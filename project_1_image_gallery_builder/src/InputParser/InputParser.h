#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H
#pragma once
#include <simple_scene/simple_scene.h>
#include <lin_alg/lin_alg.h>
#include "Scene/Scene.h"
#include "RoomBuilder/RoomBuilder.h"
#include "./InputCommand.h"

#include <unordered_map>
#include <string>

class InputParser
{
public:
    InputParser();
    ~InputParser();
    bool parse_file(std::string, std::string, Scene *);

private:
    RoomBuilder room_builder;
    Scene *scene;
    std::unordered_map<std::string, InputCommand> command_map;

    // Scene informations
    std::string texture_dir;
    int line_count;

    // Input tmps
    int row, col;
    int room_row, room_col;
    bool dimension_set;
    bool light_on;
    bool wall[4];
    std::string img_top;
    std::string img_bottom;
    std::string img_left;
    std::string img_right;

    // Registers
    bool reg_b[4];
    int reg_i[4];
    std::string reg_s[4];

    void handle_command(InputCommand, std::istringstream &);

    // utilities

    InputCommand string_to_command(std::string);

    void populate_command_map();

    bool read_input(std::istringstream &, int, int);

    void reset_value();
};

#endif