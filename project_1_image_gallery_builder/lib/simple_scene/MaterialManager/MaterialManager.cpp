#include "./MaterialManager.h"

namespace ss
{
    MaterialManager::MaterialManager() {}
    MaterialManager::~MaterialManager() {}

    void MaterialManager::add_material(Material material)
    {
        this->material_storage.push_back(material);
    }

    void MaterialManager::prepare_materials()
    {
        if (this->material_storage.size() != 0)
        {
            for (Material m : this->material_storage)
            {
                this->ambient.push_back(m.ambient);
                this->diffuse.push_back(m.diffuse);
                this->specular.push_back(m.specular);
                this->shininess.push_back(m.shininess);
                this->texture_id.push_back(m.texture_id);
                std::cout << m.texture_id << '\n';
            }
        }
    }

    void MaterialManager::use_all_materials(Shader *shader_program)
    {
        shader_program->set_vec3_arr("mat_ambient", this->ambient.size(), &this->ambient[0]);
        shader_program->set_vec3_arr("mat_diffuse", this->diffuse.size(), &this->diffuse[0]);
        shader_program->set_vec3_arr("mat_specular", this->specular.size(), &this->specular[0]);
        shader_program->set_float_arr("mat_shininess", this->shininess.size(), &this->shininess[0]);
        shader_program->set_float_arr("mat_texture_id", this->texture_id.size(), &this->texture_id[0]);
    }

    int MaterialManager::get_material_count(){
        return this->material_storage.size();
    }

}