#include "./BatchManager.h"
const int MAX_MAT = 32; // just for now

BatchManager::BatchManager()
{
    this->material_count = 0;
    this->current_batch = 0;
}

BatchManager::~BatchManager()
{
}

int BatchManager::add_material(ss::Material material)
{
    // Search for correct batch
    // We use the latest unused slot
    int mat_id = this->material_count;
    int destination_batch = this->get_destination_batch(mat_id);

    // We set the tex id to local tex_id before pushing it in already so no processing here.
    this->scene_storage[destination_batch].add_material(material);

    // Increment material count
    this->material_count += 1;

    return mat_id;
}

void BatchManager::add_mesh(ss::Mesh mesh)
{
    // Search for correct batch
    int tmp_id = mesh.mat_id;
    int destination_batch = this->get_destination_batch(tmp_id);

    mesh.mat_id = tmp_id % MAX_MAT;
    // Add mesh based on material batch
    this->scene_storage[destination_batch].add_mesh(mesh);
}

TextureInformation BatchManager::add_texture(std::string file_path, GLuint lod, GLenum internal_format, GLenum format)
{
    // Init information payload
    TextureInformation tex_info;
    tex_info.id = 32;
    tex_info.valid = 0;
    tex_info.width = 0.5;
    tex_info.height = 0.5;

    // Search for correct batch
    int mat_id = this->material_count;
    int destination_batch = this->get_destination_batch(mat_id);

    // Create and check texture validity
    int tex_valid = this->scene_storage[destination_batch].add_texture(file_path, lod, internal_format, format);
    if (tex_valid)
    {
        tex_info.id = this->scene_storage[destination_batch].get_texture_count() - 1;
        this->scene_storage[destination_batch].get_texture_data(tex_info.id, tex_info.width, tex_info.height);
        tex_info.valid = true;
    }

    return tex_info;
}

void BatchManager::add_point_light(ss::PointLight point_light)
{
    this->light_manager.add_point_light(point_light);
}

void BatchManager::next_batch()
{
    if (this->scene_storage.size())
    {
        this->current_batch = (this->current_batch + 1) % this->scene_storage.size();
    }
}

int BatchManager::get_batch_count()
{
    return this->scene_storage.size();
}

void BatchManager::build_all_batches()
{
    for (int i = 0; i < this->scene_storage.size(); i++)
    {
        this->scene_storage[i].build_scene();
    }

    this->light_manager.prepare_point_light();
}

RenderComponents BatchManager::use_current_batch(ss::Shader *shader_program)
{
    if (this->scene_storage.size())
    {
        this->scene_storage[this->current_batch].use_materials(shader_program);
        this->light_manager.use_all_point_lights(shader_program);
        return this->scene_storage[this->current_batch].get_render_components();
    }
}

void BatchManager::set_dimension(int row, int col)
{
    this->row = row;
    this->col = col;
}

int BatchManager::get_destination_batch(int id)
{
    int batch_count = this->scene_storage.size();
    int destination_batch = id / MAX_MAT;

    // This does not consider universal case. We will need to rework too many things for ID system so I'll make it a patchwork here (or a for loop which will open up more edge cases so we will assume the input is perfect)
    if (destination_batch > batch_count - 1)
    {
        this->scene_storage.push_back(Scene());
    }

    return destination_batch;
}

void BatchManager::delete_all_render_components()
{
    for (int i = 0; i < this->scene_storage.size(); i++)
    {
        this->scene_storage[i].delete_render_components();
    }
}