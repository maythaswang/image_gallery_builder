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

class InputParser{
    public: 
        InputParser();
        ~InputParser();
        bool parse_file(std::string, std::string ,Scene *); 

    private: 
        RoomBuilder room_builder;
        Scene *scene;
        std::unordered_map<std::string, InputCommand> command_map;
        
        // scene informations
        int row,col;
        std::string texture_dir;

        int line_count;

        // Registers
        int reg_i[2];
        bool reg_b[5];
        std::string reg_s[4];

        InputCommand string_to_command(std::string);

        void populate_command_map();

        void handle_command(InputCommand);
};

#endif 