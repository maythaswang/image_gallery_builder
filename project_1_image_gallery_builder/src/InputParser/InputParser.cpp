#include "./InputParser.h"

InputParser::InputParser()
{
}

InputParser::~InputParser()
{
}

bool InputParser::parse_file(std::string file_path, Scene *scene)
{
    this->scene = scene;
    std::ifstream input_file(file_path);

    if (input_file.fail())
    {
        return 0;
    }

    std::string line;
    std::string command_string;
    InputCommand command;

    while (std::getline(input_file, line))
    {
        std::cout << line << std::endl;
        std::istringstream iss(line);
        iss >> command_string;
        command = this->string_to_command(command_string);
        this->handle_command(command);
    }
}

InputCommand InputParser::string_to_command(std::string input)
{
    if (this->command_map.find(input) != this->command_map.end())
    {
        return this->command_map[input];
    }

    std::cout << "Invalid Command: " << input << '\n';
    return InputCommand::IGNORE;
}

void InputParser::populate_command_map()
{
    this->command_map = {
        {"#", InputCommand::IGNORE},
        {"size", InputCommand::SIZE},
        // {"plan", InputCommand::PLAN},
        {"room", InputCommand::ROOM},
        {"light", InputCommand::LIGHT},
        {"wall", InputCommand::WALL},
        {"image_top", InputCommand::IMAGE_TOP},
        {"image_bottom", InputCommand::IMAGE_BOTTOM},
        {"image_left", InputCommand::IMAGE_LEFT},
        {"image_right", InputCommand::IMAGE_RIGHT},

    };
}

void handle_command(InputCommand command)
{
    switch (command)
    {
    case InputCommand::SIZE:
        break;
    }
}