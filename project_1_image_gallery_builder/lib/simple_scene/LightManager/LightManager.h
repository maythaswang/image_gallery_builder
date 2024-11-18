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
     * @brief We will only use point light for now
     *
     */
    class LightManager
    {
    public:
        LightManager();
        ~LightManager();

        void add_point_light(PointLight);
        void prepare_point_light();
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