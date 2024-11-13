#include <Lab4_textured_box.h>
#include <Shader/shader.h>
#include <iostream>

RenderComponents build_box()
{
    // Build cube geometry (resizing window will distort the object since we don't have mvp matrices prepped yet.)
    std::cout << "BUILDING BOX" << std::endl;

    GeometryBuilder Geometry_builder = GeometryBuilder();
    std::vector<GLfloat> center = {0.0f, 0, 0}; // Let's have the center at origin.

    RenderComponents render_components;
    Geometry_builder.init_box(&render_components, center, 1.0f, 1.0f, 1.0f);

    return render_components;
}