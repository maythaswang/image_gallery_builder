#include "./InputParser.h"

InputParser::InputParser()
{
    this->populate_command_map();

    std::fill(this->reg_b, this->reg_b + 4, 0);
    std::fill(this->reg_i, this->reg_i + 4, 0);
    std::fill(this->reg_s, this->reg_s + 4, "");
}

InputParser::~InputParser()
{
}

bool InputParser::parse_file(std::string file_path, std::string texture_dir, BatchManager *batch_manager)
{
    // Reset values
    this->line_count = 0;
    this->dimension_set = 0;
    this->row = 0;
    this->col = 0;
    this->reset_value();

    // Set scene sources
    this->batch_manager = batch_manager;
    std::ifstream input_file(file_path);
    this->texture_dir = texture_dir + "/";

    if (input_file.fail())
    {
        return 0;
    }
    std::string foo; // Trashcan 
    std::string line;
    std::string command_string;
    InputCommand command;

    while (std::getline(input_file, line))
    {
        std::istringstream iss(line);
        iss >> command_string;
        if (iss.fail())
        {
            iss.clear();
            iss >> foo;
            command_string = "";
        }
        command = this->string_to_command(command_string);
        this->handle_command(command, iss);
        this->line_count += 1;
    }
}

void InputParser::handle_command(InputCommand command, std::istringstream &iss)
{
    bool read_success;
    switch (command)
    {
    case InputCommand::DIMENSION:
        if (this->dimension_set)
        {
            std::cout << "Error at line " << this->line_count << "! The dimension of the scene has already been defined! (" << this->row << ", " << this->col << ")\n";
        }
        else
        {
            read_success = this->read_input(iss, 2, 1);
            if (read_success)
            {
                int row = this->reg_i[0];
                int col = this->reg_i[1];

                if (row > 5 || col > 5 || row < 0 || col < 0)
                {
                    std::cout << "Error at line " << this->line_count << "! Invalid dimension" << '\n';
                }
                else
                {
                    this->row = row;
                    this->col = col;
                    this->dimension_set = 1;

                    this->room_builder.set_scene_data(this->batch_manager, row, col);
                    this->room_builder.init_basic_materials();
                }
            }
        }
        break;

    case InputCommand::INDEX:
        if (!this->dimension_set)
        {
            std::cout << "Error at line " << this->line_count << "! Scene dimension has not been set!" << '\n';
        }
        else
        {
            read_success = this->read_input(iss, 2, 1);

            if (read_success)
            {
                int i = this->reg_i[0];
                int j = this->reg_i[1];
                if (i >= this->row || j >= this->col || i < 0 || j < 0)
                {
                    std::cout << "Error at line " << this->line_count << "! Invalid room index!" << '\n';
                }
                else
                {
                    this->room_row = this->reg_i[0];
                    this->room_col = this->reg_i[1];
                }
            }
            else
            {
                std::cout << "Error at line " << this->line_count << "! Invalid room index!" << '\n';
            }
        }
        break;

    case InputCommand::LIGHT:
        if (!this->dimension_set)
        {
            std::cout << "Error at line " << this->line_count << "! Scene dimension has not been set!" << '\n';
        }
        else
        {
            read_success = this->read_input(iss, 1, 0);

            if (read_success)
            {
                this->light_on = this->reg_b[0];
            }
        }
        break;

    case InputCommand::WALL:
        if (!this->dimension_set)
        {
            std::cout << "Error at line " << this->line_count << "! Scene dimension has not been set!" << '\n';
        }
        else
        {
            read_success = this->read_input(iss, 4, 0);

            if (read_success)
            {
                this->wall[0] = this->reg_b[0];
                this->wall[1] = this->reg_b[1];
                this->wall[2] = this->reg_b[2];
                this->wall[3] = this->reg_b[3];
            }
        }
        break;

    case InputCommand::IMAGE_TOP:
        if (!this->dimension_set)
        {
            std::cout << "Error at line " << this->line_count << "! Scene dimension has not been set!" << '\n';
        }
        else
        {
            read_success = this->read_input(iss, 1, 2);

            if (read_success)
            {
                this->img_top = this->texture_dir + this->reg_s[0];
            }
        }

        break;

    case InputCommand::IMAGE_BOTTOM:
        if (!this->dimension_set)
        {
            std::cout << "Error at line " << this->line_count << "! Scene dimension has not been set!" << '\n';
        }
        else
        {
            read_success = this->read_input(iss, 1, 2);

            if (read_success)
            {
                this->img_bottom = this->texture_dir + this->reg_s[0];
            }
        }
        break;

    case InputCommand::IMAGE_LEFT:
        if (!this->dimension_set)
        {
            std::cout << "Error at line " << this->line_count << "! Scene dimension has not been set!" << '\n';
        }
        else
        {
            read_success = this->read_input(iss, 1, 2);

            if (read_success)
            {
                this->img_left = this->texture_dir + this->reg_s[0];
            }
        }
        break;

    case InputCommand::IMAGE_RIGHT:
        if (!this->dimension_set)
        {
            std::cout << "Error at line " << this->line_count << "! Scene dimension has not been set!" << '\n';
        }
        else
        {
            read_success = this->read_input(iss, 1, 2);

            if (read_success)
            {
                this->img_right = this->texture_dir + this->reg_s[0];
            }
        }
        break;

    case InputCommand::BUILD_ROOM:
        if (!this->dimension_set)
        {
            std::cout << "Error at line " << this->line_count << "! Scene dimension has not been set!" << '\n';
        }

        this->room_builder.build_room(this->room_row, this->room_col, this->light_on, this->wall[0], this->wall[1], this->wall[2], this->wall[3], this->img_top, this->img_bottom, this->img_left, this->img_right);
        this->img_top = "";
        this->img_bottom = "";
        this->img_left = "";
        this->img_right = "";

        break;

    // Make one for reset
    default:
        break;
    }
}

bool InputParser::read_input(std::istringstream &iss, int size, int input_type)
{
    std::string foo; // just a trash can

    if (size > 4 || input_type > 2)
    {
        return 0;
    }

    for (int i = 0; i < size; i++)
    {
        switch (input_type)
        {
        case 0: // bool
            iss >> this->reg_b[i];
            break;
        case 1:
            iss >> this->reg_i[i];
            break;
        case 2:
            iss >> this->reg_s[i];
            break;
        default:
            break;
        }

        if (iss.fail())
        {
            iss.clear();
            iss >> foo;
            return 0;
        }
    }

    return 1;
}

void InputParser::reset_value()
{
    std::fill(this->reg_b, this->reg_b + 4, 0);
    std::fill(this->reg_i, this->reg_i + 4, 0);
    std::fill(this->reg_s, this->reg_s + 4, "");

    this->light_on = 0;
    std::fill(this->wall, this->wall + 4, 0);
    this->img_top = "";
    this->img_bottom = "";
    this->img_left = "";
    this->img_right = "";
}

InputCommand InputParser::string_to_command(std::string input)
{
    if (this->command_map.find(input) != this->command_map.end())
    {
        return this->command_map[input];
    }

    std::cout << "Error! Invalid Command at line " << this->line_count << ": " << input << '\n';
    return InputCommand::IGNORE;
}

void InputParser::populate_command_map()
{
    this->command_map = {
        {"", InputCommand::IGNORE},
        {"#", InputCommand::IGNORE},
        {"dimension", InputCommand::DIMENSION},
        {"index", InputCommand::INDEX},
        {"light", InputCommand::LIGHT},
        {"wall", InputCommand::WALL},
        {"image_top", InputCommand::IMAGE_TOP},
        {"image_bottom", InputCommand::IMAGE_BOTTOM},
        {"image_left", InputCommand::IMAGE_LEFT},
        {"image_right", InputCommand::IMAGE_RIGHT},
        {"build_room", InputCommand::BUILD_ROOM},
    };
}
