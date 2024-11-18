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
    this->mesh_storage.push_back(mesh);
}

void Scene::add_point_light(ss::PointLight point_light){
    this->light_manager.add_point_light(point_light);
}

void Scene::build_scene()
{
    this->render_components_updated = false;
    int offset = 0;

    for (ss::Mesh m : this->mesh_storage)
    {
        offset = this->vertices.size();
        for (int i = 0; i < m.vertices.size(); i++)
        {
            this->vertices.push_back(m.vertices[i]);
            this->normals.push_back(m.normals[i]);
            this->tex_coords.push_back(m.tex_coord[i * 2]);
            this->tex_coords.push_back(m.tex_coord[i * 2 + 1]);
            this->material_ids.push_back(m.mat_id);
        }
        
        for (int i = 0; i < m.indices.size(); i++)
        {
            this->indices.push_back(m.indices[i] + offset);
        }
    }

    this->render_components.n_vert = this->vertices.size();
    this->render_components.n_inds = this->indices.size();

    this->init_buf();
    this->material_manager.prepare_materials();
    this->light_manager.prepare_point_light();
}

RenderComponents Scene::get_render_components()
{
    if (!this->render_components_updated)
    {
        this->build_scene();
    }
    return this->render_components;
}

void Scene::use_materials(ss::Shader *shader_program)
{
    this->texture_manager.use_all_textures(shader_program);
    this->material_manager.use_all_materials(shader_program);
    this->light_manager.use_all_point_lights(shader_program);
}

void Scene::init_buf()
{
    if (!this->render_components_initialized)
    {
        glGenVertexArrays(1, this->render_components.VAO);
        glGenBuffers(4, this->render_components.VBO);
        glGenBuffers(1, this->render_components.EBO);
    }

    glBindVertexArray(this->render_components.VAO[0]);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, this->render_components.VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->render_components.n_vert * 3, &this->vertices[0][0], GL_STATIC_DRAW);
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

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->render_components.EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->render_components.n_inds * 3, &this->indices[0][0], GL_STATIC_DRAW);

    // Unbind VAOs, VBOs, EBOs
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->render_components_updated = true;
}
