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

    /**
     * @brief Parse the scene data file and generate the scene accordingly using batch_manager
     *
     * @param file_path scene data file path
     * @param texture_dir texture directory
     * @param batch_manager batch manager
     * @return true if successs
     * @return false if failed
     */
    bool parse_file(std::string file_path, std::string texture_dir, BatchManager *batch_manager);

private:
    RoomBuilder room_builder;
    BatchManager *batch_manager;
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

    /**
     * @brief Handle each command
     *
     * @param command
     * @param iss string stream containting the line information (but not command)
     */
    void handle_command(InputCommand command, std::istringstream &iss);

    // utilities

    /**
     * @brief Turns command string into command enum
     *
     * @param input string command
     * @return The corresponding command if there exist a match,
     * @return otherwise return command ignore and print errors
     */
    InputCommand string_to_command(std::string input);

    /**
     * @brief Populate string to command map
     *
     */
    void populate_command_map();

    /**
     * @brief read input based from the provided information
     *
     * @param iss string stream containing the line information
     * @param size the number of items you wish to read
     * @param input_type input type where {0:bool, 1:int, 2:string}
     *
     * @return true if success,
     * @return false if failure
     */
    bool read_input(std::istringstream &iss, int size, int input_type);

    /**
     * @brief Reset all intermediate states to default
     *
     */
    void reset_value();
};

#endif