#ifndef SS_TEXTURE_MANAGER_H
#define SS_TEXTURE_MANAGER_H
#pragma once

#include "../SS_GLcommon.h"
#include "../Texture/Texture.h"
#include "../Shader/Shader.h"

#include <vector>
#include <string>

namespace ss
{

    /**
     * @brief Class for storing multiple texture objects
     * @note For ease of use when batching
     *
     */
    class TextureManager
    {
    public:
        /**
         * @brief Construct a new Texture Manager object
         *
         */
        TextureManager();
        ~TextureManager();

        /**
         * @brief
         * @note This right now requires the texture to be added in correct order from 1..n..n+1
         * @param file_path
         * @param lod
         * @param internal_format
         * @param format
         * @return true if success and false otherwise
         */
        bool create_texture(std::string, GLuint, GLenum, GLenum);

        /**
         * @brief Activate texture slots and bind texture
         *
         */
        void activate_all_textures();

        /**
         * @brief Set texture uniforms
         *
         */
        void use_all_textures(Shader *);

        /**
         * @brief
         *
         * @param texture_id texture id
         * @param width width of the texture
         * @param height height of the texture
         */
        void get_texture_data(int texture_id, GLfloat &width, GLfloat &height);

        /**
         * @brief Get number of textures stored.
         *
         * @return number of textures
         */
        int get_texture_count();

    private:
        std::vector<Texture> textures_storage;
        std::vector<int> texture_ids;
        // std::queue<GLuint> empty_slots; Let's not handle this since we won't be using it here
    };
}
#endif