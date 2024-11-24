#include "./BatchManager.h"
BatchManager::BatchManager()
{
    this->material_count = 0;
    this->current_batch = -1;
    this->batch_count = 0;
}

BatchManager::~BatchManager()
{
}

void BatchManager::add_material(ss::Material){

}

void BatchManager::add_mesh(ss::Mesh){

}

void BatchManager::next_batch(){
    if(batch_count){
        this->current_batch = (this->current_batch + 1)% this->batch_count;
    }
}

void BatchManager::get_render_components(){

}

int BatchManager::get_batch_count(){
    return this->batch_count;
}

void BatchManager::build_all_batches(){

}

void BatchManager::use_current_batch(){
    
}

void BatchManager::set_dimension(int row, int col){
    this->row = row; 
    this->col = col;
}