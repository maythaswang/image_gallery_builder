#version 430 core



in vec3 normal;
in vec2 tex_coord;
in float mat_id;

out vec4 FragColor;

//  struct Material {
const int n_mat = 32;
uniform vec3 mat_ambient[n_mat];            // Ambient color
uniform vec3 mat_diffuse[n_mat];            // Diffuse color
uniform vec3 mat_specular[n_mat];           // Specular color (not used in this shader)
uniform float mat_shininess[n_mat];         // Shininess factor
uniform float mat_texture_id[n_mat];        // If not 0, use texture instead of ambient/diffuse colors
// };

uniform sampler2D u_textures[32];
// uniform Material mat[1];
// uniform float mat_texture_id[1];


void main()
{
    // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    // FragColor = vec4(tex_coord.x, tex_coord.y, 0.0f, 1.0f);
    int cur_mat_id = int(mat_id + 0.1);

    int texture_index = int(mat_texture_id[cur_mat_id] + 0.1); // Just a stupid hack so that things can just work for now
    if(texture_index != 0){ // 0 ist for no texture
        FragColor = texture(u_textures[texture_index-1],tex_coord);
    } else {
        FragColor = vec4(1, mat_ambient[cur_mat_id][1] , mat_ambient[cur_mat_id][2], 1.0f);
    }


    // FragColor = vec4(1, mat_texture_id[cur_mat_id] , 0, 1);
    // FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}