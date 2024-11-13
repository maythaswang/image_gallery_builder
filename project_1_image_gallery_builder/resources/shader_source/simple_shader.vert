#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 a_tex_coord;
layout (location = 2) in float a_tex_id;

out vec2 tex_coord;
out float tex_id;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    tex_coord = vec2(a_tex_coord.x, a_tex_coord.y);
    tex_id = a_tex_id;
}