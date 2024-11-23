#include "./InputParser.h"

InputParser::InputParser()
{
    this->populate_command_map();
}

InputParser::~InputParser()
{
}

bool InputParser::parse_file(std::string file_path, std::string texture_dir, Scene *scene)
{
    // Reset values
    this->line_count = 0;
    this->row = 0;
    this->col = 0;
    std::fill(this->reg_i, this->reg_i + 5, 0);
    std::fill(this->reg_b, this->reg_b + 2, 0);
    std::fill(this->reg_s, this->reg_s + 4, "");

    // Set scene sources
    this->scene = scene;
    std::ifstream input_file(file_path);
    this->texture_dir = texture_dir;

    if (input_file.fail())
    {
        return 0;
    }

    std::string line;
    std::string command_string;
    InputCommand command;

    while (std::getline(input_file, line))
    {
        // std::cout << line << std::endl;
        std::istringstream iss(line);
        iss >> command_string;
        command = this->string_to_command(command_string);
        this->handle_command(command);
        this->line_count += 1;
    }
}

InputCommand InputParser::string_to_command(std::string input)
{
    if (this->command_map.find(input) != this->command_map.end())
    {
        return this->command_map[input];
    }

    std::cout << "Invalid Command at line " << this->line_count << ": " << input << '\n';
    return InputCommand::IGNORE;
}

void InputParser::populate_command_map()
{
    this->command_map = {
        {"#", InputCommand::IGNORE},
        {"size", InputCommand::SIZE},
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

void InputParser::handle_command(InputCommand command)
{
    switch (command)
    {
    case InputCommand::SIZE:
        break;

    case InputCommand::INDEX:
        break;

    case InputCommand::LIGHT:
        break;

    case InputCommand::WALL:
        break;

    case InputCommand::IMAGE_TOP:
        break;

    case InputCommand::IMAGE_BOTTOM:
        break;

    case InputCommand::IMAGE_LEFT:
        break;

    case InputCommand::IMAGE_RIGHT:
        break;

    case InputCommand::BUILD_ROOM:
        break;

    default:
        break;
    }
}