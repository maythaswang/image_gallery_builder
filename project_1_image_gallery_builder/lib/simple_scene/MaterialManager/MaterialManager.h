#ifndef SS_MATERIAL_MANAGER
#define SS_MATERIAL_MANAGER
#pragma once
#include "../SS_GLCommon.h"
#include "../SceneComponents/Material.h"
#include "../Shader/Shader.h"

#include <vector>

namespace ss
{
    /**
     * @brief 
     * @note AS FOR WHY I DON'T HAVE A MATERIAL ID <-> TEXTURE ID MAPPING SYSTEM. I DON'T KNOW TOO, DIDN'T HAVE TIME TO THINK AND NOW I AM SUFFERING THE CONSEQUENCE OF IT.
     */
    class MaterialManager
    {
    public:
        MaterialManager();
        ~MaterialManager();

        void add_material(Material);
        void prepare_materials();
        void use_all_materials(Shader* shader_program);
        int get_material_count();


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