#version 430 core

in vec3 normal;
in vec2 tex_coord;
in float tex_id;

out vec4 FragColor;

uniform sampler2D u_textures[32];

void main()
{
    // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    // FragColor = vec4(tex_coord.x, tex_coord.y, 0.0f, 1.0f);
    // int texture_index = int(tex_id + 0.2); // Just a stupid hack so that things can just work for now
    // if(texture_index != 0){ // 0 ist for no texture
    //     FragColor = texture(u_textures[texture_index-1],tex_coord);
    // } else {
    //     FragColor = vec4(1, 0.0f, 0.0f, 1.0f);
    // }
    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}