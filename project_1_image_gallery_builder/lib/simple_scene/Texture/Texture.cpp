#include "./Texture.h"
namespace ss
{
    Texture::Texture()
    {
        this->has_texture = 0;
        this->width = 0;
        this->height = 0;
    }

    Texture::~Texture()
    {
        this->has_texture = 0;
        this->delete_texture();
    }

    GLuint Texture::get_texture_id()
    {
        return this->texture_id;
    }

    bool Texture::setup_texture(std::string file_path, GLuint lod, GLenum internal_format, GLenum format)
    {
        if (!this->has_texture)
        {
            glGenTextures(1, &this->texture_id);
            this->has_texture = 1;
        }
        glBindTexture(GL_TEXTURE_2D, this->texture_id);

        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // note that we set the container wrapping method to GL_CLAMP_TO_EDGE
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        bool status = this->read_file(file_path, lod, internal_format, format);

        // unbind
        glBindTexture(GL_TEXTURE_2D, 0);

        if (!status)
        {
            this->delete_texture();
        }

        return status;
    }

    bool Texture::read_file(std::string file_path, GLuint lod, GLenum internal_format, GLenum format)
    {
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        // stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        unsigned char *data = stbi_load(file_path.c_str(), &width, &height, &nrChannels, 0);
        GLenum img_format = format;
        if (data)
        {
            switch (nrChannels)
            {
            case 1:
                img_format = GL_RED;
                break;
            case 2:
                img_format = GL_RG;
                break;
            case 3:
                img_format = GL_RGB;
                break;
            case 4:
                img_format = GL_RGBA;
                break;

            default:
                break;
            }

            glBindTexture(GL_TEXTURE_2D, this->texture_id);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            glTexImage2D(GL_TEXTURE_2D, lod, internal_format, width, height, 0, img_format, GL_UNSIGNED_BYTE, data);

            glGenerateMipmap(GL_TEXTURE_2D);

            glBindTexture(GL_TEXTURE_2D, 0);

            this->width = width;
            this->height = height;
        }
        else
        {
            std::cout << "Failed to load texture:" << file_path << std::endl;
            return 0;
        }
        stbi_image_free(data);
        return 1;
    }

    void Texture::delete_texture()
    {
        if (this->has_texture)
        {
            glDeleteTextures(1, &this->texture_id);
            this->has_texture = 0;
        }
    }

    bool Texture::get_has_texture()
    {
        return this->has_texture;
    }

    void Texture::use_texture(GLuint id)
    {
        glActiveTexture(GL_TEXTURE0 + id);
        glBindTexture(GL_TEXTURE_2D, this->texture_id);
    }

    void Texture::get_info(GLfloat &width, GLfloat &height)
    {
        width = this->width;
        height = this->height;
    }
}