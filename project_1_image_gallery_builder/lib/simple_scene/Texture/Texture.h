#ifndef SS_TEXTURE_H
#define SS_TEXTURE_H
#pragma once
#include "../SS_GLCommon.h"

#include <string>
#include <iostream>

namespace ss
{
    class Texture
    {
    public:
        Texture();
        Texture(bool);
        ~Texture();

        /**
         * @brief
         *
         * @param file_path
         * @param lod
         * @param internal_format
         * @param format
         * @return true
         * @return false
         */
        bool setup_texture(std::string, GLuint, GLenum, GLenum);

        /**
         * @brief Use the current texture
         *
         * @param texture_id id you wish to bind the texture to
         */
        void use_texture(GLuint);

        /**
         * @brief Delete the current texture
         *
         */
        void delete_texture();

        /**
         * @brief Get the texture id object
         *
         * @return texture id
         */
        GLuint get_texture_id();

        /**
         * @brief Get status whether texture exist or not
         *
         * @return true if texture exist
         */
        bool get_has_texture();

    private:
        GLuint texture_id;
        bool has_texture;
        /**
         * @brief
         *
         * @param file_path
         * @param lod
         * @param internal_format
         * @param format
         * @return true
         * @return false
         */
        bool read_file(std::string, GLuint, GLenum, GLenum);
    };
}
#endif