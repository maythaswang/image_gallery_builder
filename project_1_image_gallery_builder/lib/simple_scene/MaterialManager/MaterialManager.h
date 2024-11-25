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
     * @brief Store, Prepare, Use materials. 
     * @note Due to time constraint, there is no proper material <=> texture ID system.
     */
    class MaterialManager
    {
    public:
        MaterialManager();
        ~MaterialManager();
        
        /**
         * @brief Add materials to the material storage in this class.
         * @param material Material object
         */
        void add_material(Material);

        /**
         * @brief Prepare all materials for the use stage after all required materials have been added.
         * @note Due to time constraint in implementation, this function should only be called once.
         * @note Any subsequent calls will create unintended effects (since the vector is not rebuilt but appened.) 
         */
        void prepare_materials();

        /**
         * @brief Use all prepared materials as uniforms.
         * 
         * @param shader_program 
         */
        void use_all_materials(Shader* shader_program);

        /**
         * @brief Get total material count
         * 
         * @return number of materials
         */
        int get_material_count();


    private:
        std::vector<Material> material_storage;
        std::vector<lin_alg::vec3> ambient; 
        std::vector<lin_alg::vec3> diffuse; 
        std::vector<lin_alg::vec3> specular;
        std::vector<float> shininess;
        std::vector<float> texture_id;
        std::vector<int> is_emittor;
    };
}
#endif