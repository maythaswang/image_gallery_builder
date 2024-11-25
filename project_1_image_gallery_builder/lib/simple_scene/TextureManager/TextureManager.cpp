#include "./TextureManager.h"
const int MAX_TEX = 32;

namespace ss
{
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
            // std::cout << "Successfully created_texture id: " << texture.get_texture_id() << std::endl;
            return 1;
        }
        return 0;
    }

    void TextureManager::activate_all_textures()
    {
        if (this->textures_storage.size() > 1) // This is because we reserved slot 0 for no tex
        {
            for (Texture texture : this->textures_storage)
            {
                texture.use_texture(texture.get_texture_id());
            }
        }
    }

    void TextureManager::use_all_textures(Shader *shader_program)
    {
        if (this->textures_storage.size() > 1) // This is because we reserved slot 0 for no tex
        {
            this->activate_all_textures();
            shader_program->set_int_arr("u_textures", this->texture_ids.size(), &this->texture_ids[0]);
        }
    }

    void TextureManager::get_texture_data(int texture_id, GLfloat &width, GLfloat &height)
    {
        if (texture_id < this->textures_storage.size() && texture_id >= 0)
        {
            this->textures_storage[texture_id].get_info(width, height);
        }
        else
        {
            width = 0;
            height = 0;
        }
    }

    int TextureManager::get_texture_count()
    {
        return this->textures_storage.size();
    }
}