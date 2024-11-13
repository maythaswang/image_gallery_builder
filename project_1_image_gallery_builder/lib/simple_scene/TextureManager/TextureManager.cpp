#include "./TextureManager.h"
TextureManager::TextureManager()
{
    this->textures_storage.push_back(Texture()); // Add in empty texture for slot 0
}

TextureManager::~TextureManager()
{
    // Remove textures;
}

bool TextureManager::create_texture(std::string file_path, GLuint lod, GLenum internal_format, GLenum format)
{
    Texture texture = Texture();
    texture.setup_texture(file_path, lod, internal_format, format);
    if (texture.get_has_texture())
    {
        this->textures_storage.push_back(texture);
        this->texture_ids.push_back(texture.get_texture_id());
        std::cout << "Successfully created_texture id: " << texture.get_texture_id() << std::endl;
        return 1;
    }
    return 0;
}

void TextureManager::activate_all_textures()
{
    for (Texture texture : this->textures_storage)
    {
        texture.use_texture(texture.get_texture_id());
    }
}

void TextureManager::use_all_textures(Shader *shader_program)
{
    this->activate_all_textures();
    shader_program->set_int_arr("u_textures", this->texture_ids.size(), &this->texture_ids[0]);
}