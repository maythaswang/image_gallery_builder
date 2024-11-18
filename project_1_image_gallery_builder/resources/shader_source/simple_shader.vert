#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_tex_coord;
layout (location = 3) in float a_mat_id;

out vec3 normal;
out vec2 tex_coord;
out float mat_id;

// Uniform Variables
uniform mat4 modelview;
uniform mat4 projection;

void main()
{
    gl_Position = projection * modelview * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    // gl_Position =  vec4(aPos.x, aPos.y, aPos.z, 1.0);
    normal = a_normal;
    tex_coord = vec2(a_tex_coord.x, a_tex_coord.y);
    mat_id = a_mat_id;
}