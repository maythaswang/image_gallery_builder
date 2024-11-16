#ifndef SS_MATERIAL_H
#define SS_MATERIAL_H
#pragma once

#include <lin_alg/lin_alg.h>

namespace ss
{
    struct Material{
        float texture_id; // If not 0 we can ignore ambient and diffuse values; 

        lin_alg::vec3 ambient;
        lin_alg::vec3 diffuse; 
        lin_alg::vec3 specular; // I'm not gonna write one for specular map for now.
        
        float shininess;
        bool has_tex = 0;
        
    };
}

#endif 