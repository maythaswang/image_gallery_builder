#ifndef SS_LIGHT_MANAGER_H
#define SS_LIGHT_MANAGER_H
#pragma once

#include "../SS_GLCommon.h"
#include "../SceneComponents/Light.h"
#include "../Shader/Shader.h"

#include <vector>

namespace ss
{
    /**
     * @brief Store, Prepare, and Use light components.
     * @note We will only use point light for now
     *
     */
    class LightManager
    {
    public:
        LightManager();
        ~LightManager();

        /**
         * @brief Add pointlight to the light storage of this class.
         * @param point_light PointLight object
         */
        void add_point_light(PointLight);

        /**
         * @brief Prepare all point lights for the use stage after all required lights have been added.
         * @note Due to time constraint in implementation, this function should only be called once.
         * @note Any subsequent calls will create unintended effects (since the vector is not rebuilt but appened.) 
         * 
         */
        void prepare_point_light();

        /**
         * @brief Use all prepared point lights as uniforms
         * 
         * @param shader_program 
         */
        void use_all_point_lights(Shader *shader_program);

    private:
        std::vector<PointLight> point_light_storage;
        std::vector<lin_alg::vec3> position;
        std::vector<lin_alg::vec3> ambient;
        std::vector<lin_alg::vec3> diffuse;
        std::vector<lin_alg::vec3> specular;
        std::vector<float> constant;
        std::vector<float> linear;
        std::vector<float> quadratic;
    };
}
#endif