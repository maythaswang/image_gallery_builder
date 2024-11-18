#ifndef SS_LIGHT_H
#define SS_LIGHT_H
#pragma once

#include <lin_alg/lin_alg.h>

namespace ss
{
    struct PointLight{
        lin_alg::vec3 position;

        lin_alg::vec3 ambient;
        lin_alg::vec3 diffuse;
        lin_alg::vec3 specular;

        // Attenuation
        float constant; 
        float linear;
        float quadratic;
    };

    struct DirectionalLight{
        lin_alg::vec3 direction;

        lin_alg::vec3 ambient;
        lin_alg::vec3 diffuse;
        lin_alg::vec3 specular;
    };



    struct SpotLight{
        lin_alg::vec3 position;
        lin_alg::vec3 direction;
        float cutoff;
        float outer_cutoff;

        lin_alg::vec3 ambient;
        lin_alg::vec3 diffuse;
        lin_alg::vec3 specular;

        // Attenuation
        float constant; 
        float linear;
        float quadratic;
    };
}

#endif