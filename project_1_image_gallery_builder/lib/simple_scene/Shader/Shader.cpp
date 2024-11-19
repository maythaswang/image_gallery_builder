#include "./Shader.h"
namespace ss
{
    Shader::Shader()
    {
        this->has_program = false;
        this->shader_id = 0;
    }

    GLuint Shader::compile_shader(std::string fileName, GLenum SHADER_TYPE)
    {
        // Had to make a copy, otherwise .c_str() will throw out junk since the reference is no longer valid.
        std::string file_content = this->read_shader_file(fileName);
        const char *shader_src = file_content.c_str();

        unsigned int shader = glCreateShader(SHADER_TYPE);
        glShaderSource(shader, 1, &shader_src, NULL);
        glCompileShader(shader);

        int success;
        char info_log[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        // For Debugging Purposes
        std::string shader_type_string = (SHADER_TYPE == GL_VERTEX_SHADER) ? "GL_VERTEX_SHADER" : (SHADER_TYPE == GL_FRAGMENT_SHADER) ? "GL_FRAGMENT_SHADER"
                                                                                                                                      : "UNKNOWN_TYPE";

        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, info_log);
            std::cout << "ERROR::SHADER::" << shader_type_string << "::COMPILATION_FAILED\n"
                      << info_log << std::endl;
        }

        return shader;
    }

    void Shader::link_shader(GLuint shader)
    {

        // Check if we have the shader program initialized
        if (!this->has_program)
        {
            this->shader_id = glCreateProgram();
            this->has_program = true;
        }

        GLuint shader_program = this->shader_id;
        glAttachShader(shader_program, shader);
        glLinkProgram(shader_program);

        int success;
        char info_log[512];
        glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader_program, 512, NULL, info_log);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                      << info_log << std::endl;
        }
        glDeleteShader(shader);
    }

    std::string Shader::read_shader_file(std::string file_name)
    {
        std::ifstream input_file(file_name);
        std::stringstream buffer;
        buffer << input_file.rdbuf();
        return buffer.str();
    }

    GLuint Shader::get_shader_id()
    {
        return this->shader_id;
    }

    void Shader::delete_shader()
    {
        glDeleteProgram(this->shader_id);

        // We no longer have the shader program.
        this->has_program = false;
    }

    void Shader::use()
    {
        glUseProgram(this->shader_id);
    }

    // Utilities Setter for Uniform Variables
    // ----------------------------------------------------------------------------

    void Shader::set_bool(const std::string &name, bool value)
    {
        glUniform1i(glGetUniformLocation(this->shader_id, name.c_str()), (int)value);
    };

    void Shader::set_int(const std::string &name, int value)
    {
        glUniform1i(glGetUniformLocation(this->shader_id, name.c_str()), value);
    }

    void Shader::set_float(const std::string &name, float value)
    {
        glUniform1f(glGetUniformLocation(this->shader_id, name.c_str()), value);
    }

    void Shader::set_int_arr(const std::string &name, int count, int *value)
    {
        glUniform1iv(glGetUniformLocation(this->shader_id, name.c_str()), count, value);
    }

    void Shader::set_float_arr(const std::string &name, int count, float *value)
    {
        glUniform1fv(glGetUniformLocation(this->shader_id, name.c_str()), count, value);
    }

    void Shader::set_vec3(const std::string &name, const lin_alg::vec3 &value)
    {
        glUniform3fv(glGetUniformLocation(this->shader_id, name.c_str()), 1, reinterpret_cast<const float *>(&value));
    }

    void Shader::set_vec3_arr(const std::string &name, const int count, const lin_alg::vec3 *value)
    {
        glUniform3fv(glGetUniformLocation(this->shader_id, name.c_str()), count, reinterpret_cast<const float *>(value));
    }

    void Shader::set_mat4(const std::string &name, const lin_alg::mat4 &value)
    {
        glUniformMatrix4fv(glGetUniformLocation(this->shader_id, name.c_str()), 1, GL_TRUE, &value[0][0]);
    }
}