#ifndef SS_MATERIAL_MANAGER
#define SS_MATERIAL_MANAGER
#pragma once
#include "../SS_GLCommon.h"
#include "../Material/Material.h"

#include <vector>

namespace ss
{
    class MaterialManager
    {
    public:
        MaterialManager();
        ~MaterialManager();

        void add_material(Material);
        void use_all_materials();

    private:
        std::vector<Material> material_storage;
    };
}
#endif