#version 430 core

in vec4 vert_pos;
in vec3 normal;
in vec2 tex_coord;
in float mat_id;

out vec4 FragColor;

// As to why no struct, I don't have time to change it to UBO yet, maybe later.

const float AMBIENT_MULTIPLIER = 0.2f;

// MATERIALS
const int n_mat = 32;
uniform vec3 mat_ambient[n_mat];     // Ambient color
uniform vec3 mat_diffuse[n_mat];     // Diffuse color
uniform vec3 mat_specular[n_mat];    // Specular color
uniform float mat_shininess[n_mat];  // Shininess factor
uniform float mat_texture_id[n_mat]; // If not 0, use texture instead of
                                     // ambient/diffuse colors

// POINT LIGHTS
const int n_point_light_max = 32;
uniform int n_point_light;
uniform vec3 pl_position[n_point_light_max];
uniform vec3 pl_ambient[n_point_light_max];
uniform vec3 pl_diffuse[n_point_light_max];
uniform vec3 pl_specular[n_point_light_max];
uniform float pl_constant[n_point_light_max];
uniform float pl_linear[n_point_light_max];
uniform float pl_quadratic[n_point_light_max];

uniform sampler2D u_textures[32];

uniform vec3 eye_position; // Haven't added in

// Use Blinn-Phong
vec4 compute_light(const in int light_id, const in int mat_id,
                   const in vec3 obj_normal, const in vec3 eye_direction,
                   const in vec3 current_pos) {
  // Load Material Values
  int tex_id = int(mat_texture_id[mat_id] +0.1f);
  vec3 diffuse = (tex_id == 0) ? mat_diffuse[mat_id] : vec3(texture(u_textures[tex_id-1], tex_coord));
  vec3 specular = mat_specular[mat_id];
  float shininess = mat_shininess[mat_id];
  vec3 norm = normalize(obj_normal);

  // ambient
  // ambient *= AMBIENT_MULTIPLIER;

  // diffuse (lambertian reflection)
  vec3 light_direction = normalize(pl_position[light_id] - current_pos);
  float lambertian_term = max(dot(light_direction, norm), 0.0f);
  diffuse *= pl_diffuse[light_id] * lambertian_term;

  // specular
  vec3 halfvec = normalize(light_direction + eye_direction);
  float specular_term = pow(max(dot(halfvec, norm), 0.0f), shininess);
  specular *= pl_specular[light_id] * specular_term;

  // attenuation
  float distance = length(pl_position[light_id] - current_pos);
  float atten_divide = (pl_constant[light_id] + pl_linear[light_id] * distance +
                        pl_quadratic[light_id] * pow(distance, 2));
  float attenuation = (atten_divide > 0) ? 1 / atten_divide : 0;

  return vec4(diffuse * attenuation + specular * attenuation, 1.0f);
  // return vec4(diffuse, 1.0f);
}

void main() {

  int cur_mat_id = int(mat_id + 0.1);

  if (cur_mat_id < 32) {

    // We will move this elsewhere
    int texture_index = int(mat_texture_id[cur_mat_id] + 0.1); // Just a
    // stupid hack so that things can just work for now if (texture_index != 0)

    if(texture_index < 32){

      // ambient multiplier (Checks if the material is an emitter and then proceed
      // as follows)
      // Find a way to check emittor instead
      float amb_mult = (cur_mat_id == 4) ? 0.7f : AMBIENT_MULTIPLIER;

      vec4 colour;
      if (texture_index != 0) { // 0 ist for no texture
        colour = texture(u_textures[texture_index - 1], tex_coord) * amb_mult;
      } else {
        colour = vec4(mat_ambient[cur_mat_id] * amb_mult, 1.0f);
      }

      vec3 current_pos = vert_pos.xyz / vert_pos.w;
      vec3 eye_direction = normalize(eye_position - current_pos);

      for (int i = 0; i < n_point_light; i++) {
        colour +=
            compute_light(i, cur_mat_id, normal, eye_direction, current_pos);
      }
      FragColor = colour;
    }
    
    else {FragColor = vec4(0, 0, 0, 1);}

  } else {
    FragColor = vec4(0, 1, 0, 1);
  }
}