#include "./LightManager.h"

namespace ss
{
    LightManager::LightManager()
    {
    }

    LightManager::~LightManager()
    {
    }

    void LightManager::add_point_light(PointLight point_light)
    {
        this->point_light_storage.push_back(point_light);
    }

    void LightManager::prepare_point_light()
    {
        if (this->point_light_storage.size() != 0)
        {
            for (PointLight p : this->point_light_storage)
            {
                this->position.push_back(p.position);
                this->ambient.push_back(p.ambient);
                this->diffuse.push_back(p.diffuse);
                this->specular.push_back(p.specular);
                this->constant.push_back(p.constant);
                this->linear.push_back(p.linear);
                this->quadratic.push_back(p.quadratic);
            }
        }
    }

    void LightManager::use_all_point_lights(Shader *shader_program)
    {
        shader_program->set_vec3_arr("pl_position", this->position.size(), &this->position[0]);
        shader_program->set_vec3_arr("pl_ambient", this->ambient.size(), &this->ambient[0]);
        shader_program->set_vec3_arr("pl_diffuse", this->diffuse.size(), &this->diffuse[0]);
        shader_program->set_vec3_arr("pl_specular", this->specular.size(), &this->specular[0]);
        shader_program->set_float_arr("pl_constant", this->constant.size(), &this->constant[0]);
        shader_program->set_float_arr("pl_linear", this->linear.size(), &this->linear[0]);
        shader_program->set_float_arr("pl_quadratic", this->quadratic.size(), &this->quadratic[0]);
    }
}