#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#pragma once
#include <GLCommon.h>
#include <Texture/Texture.h>
#include <Shader/Shader.h>

#include <vector>
#include <string>
// #include <queue>

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
    // void delete_texture();

private:
    std::vector<Texture> textures_storage;
    std::vector<int> texture_ids;
    // std::queue<GLuint> empty_slots; Let's not handle this since we won't be using it here
};

#endif