#ifndef SS_MATERIAL_MANAGER
#define SS_MATERIAL_MANAGER
#pragma once
#include "../SS_GLCommon.h"
#include "../Material/Material.h"
#include "../Shader/Shader.h"

#include <vector>

namespace ss
{
    class MaterialManager
    {
    public:
        MaterialManager();
        ~MaterialManager();

        void add_material(Material);
        void prepare_materials();
        void use_all_materials(Shader* shader_program);

    private:
        std::vector<Material> material_storage;
        std::vector<lin_alg::vec3> ambient; 
        std::vector<lin_alg::vec3> diffuse; 
        std::vector<lin_alg::vec3> specular;
        std::vector<float> shininess;
        std::vector<float> texture_id;
    };
}
#endif