#ifndef SS_SHADER_H
#define SS_SHADER_H
#pragma once

#include "../SS_GLCOMMON.h"
#include <lin_alg/lin_alg.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

namespace ss
{
    /**
     * @brief Store, Initialize, Link, Compile, Destroy Shaders.
     *
     */
    class Shader
    {
    public:
        /**
         * @brief Construct a new Shader object
         *
         */
        Shader();

        /**
         * @brief Create a Shader according to the shader type specified.
         * For instance, you can create fragment and vertex shader.
         *
         * @param fileName
         * @param SHADER_TYPE
         * @return status of shader creation
         */
        GLuint compile_shader(std::string, GLenum);

        /**
         * @brief Link shader that has been built by CompileShader.
         * @note The shader that has been inputted will be deleted after this function call.
         *
         * @param shader
         */
        void link_shader(GLuint);

        /**
         * @brief Get the ShaderID
         *
         * @return GLuint
         */
        GLuint get_shader_id();

        /**
         * @brief Delete the shader program
         *
         */
        void delete_shader();

        /**
         * @brief Use the shader program.
         *
         */
        void use();

        // Utility Setter for Uniform Variable
        // ----------------------------------------------------------------------------

        void set_bool(const std::string &name, bool value);
        void set_int(const std::string &name, int value);
        void set_float(const std::string &name, float value);

        void set_int_arr(const std::string &name, int, int *);
        void set_float_arr(const std::string &name, int, float*);

        void set_vec3(const std::string &name, const lin_alg::vec3 &);
        void set_vec3_arr(const std::string &name, const int, const lin_alg::vec3 *);
        
        void set_mat4(const std::string &name, const lin_alg::mat4 &);

    private:
        GLuint shader_id;
        bool has_program;

        /**
         * @brief Read the shader file
         *
         * @param fileName
         * @return const char*
         */
        std::string read_shader_file(std::string);
    };
}
#endif