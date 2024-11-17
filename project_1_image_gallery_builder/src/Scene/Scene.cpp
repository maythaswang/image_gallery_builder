#include "./Scene.h"

Scene::Scene()
{
    this->material_manager = ss::MaterialManager();
    this->texture_manager = ss::TextureManager();

    this->render_components_initialized = false;
    this->render_components_updated = false;
}

Scene::~Scene()
{
}

void Scene::add_material(ss::Material material)
{
    material_manager.add_material(material);
}

void Scene::add_texture(std::string file_path, GLuint lod, GLenum internal_format, GLenum format)
{
    texture_manager.create_texture(file_path, lod, internal_format, format);
}

void Scene::add_mesh(ss::Mesh mesh)
{
    mesh_storage.push_back(mesh);
}

void Scene::build_scene()
{
    this->render_components_updated = false;
    int offset = 0;
    for (ss::Mesh m : mesh_storage)
    {
        for (int i = 0; i < m.vertices.size(); i++)
        {
            vertices.push_back(m.vertices[i]);
            normals.push_back(m.normals[i]);
            tex_coords.push_back(m.tex_coord[i * 2]);
            tex_coords.push_back(m.tex_coord[i * 2 + 1]);
            material_ids.push_back(m.mat_id);
        }

        for (int i = 0; i < m.indices.size(); i++)
        {
            indices.push_back(m.indices[i] + offset);
        }
    }

    this->init_buf();
}

RenderComponents Scene::get_render_components()
{
    if (!this->render_components_updated)
    {
        this->init_buf();
    }
    return this->render_components;
}

void Scene::init_buf()
{
    if (!this->render_components_initialized)
    {
        glGenVertexArrays(1, this->render_components.VAO);
        glGenBuffers(3, this->render_components.VBO);
        glGenBuffers(1, this->render_components.EBO);
    }

    glBindVertexArray(*this->render_components.VAO);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, this->render_components.VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->render_components.n_vert * 3, &this->vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);

    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, this->render_components.VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->render_components.n_vert * 3, &this->normals[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);

    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, this->render_components.VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->render_components.n_vert * 2, &this->tex_coords[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void *)0);

    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, this->render_components.VBO[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->render_components.n_vert * 1, &this->material_ids[0], GL_STATIC_DRAW);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 1 * sizeof(GLfloat), (void *)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *this->render_components.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->render_components.n_inds * 3, &indices[0], GL_STATIC_DRAW);

    // Unbind VAOs, VBOs, EBOs
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    this->render_components_updated = true;
}
