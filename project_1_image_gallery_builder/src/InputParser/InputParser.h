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
        bool parse_file(std::string, Scene *); 
        bool parse_string(std::string, Scene *);

    private: 
        RoomBuilder room_builder;
        std::unordered_map<std::string, InputCommand> command_map;
        
        int row,col;
        int plan[5][5];
        int reg_i[2];
        bool reg_b[5];
        std::string reg_s[4];
    
        InputCommand string_to_command(std::string);

        // handle command ...
};

#endif 