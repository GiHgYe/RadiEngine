#include "renderer/mesh_filter.h"
#include <fstream>

MeshFilter::MeshFilter() 
	: mesh_(nullptr)
{

}

void MeshFilter::LoadMesh(std::string mesh_file_path) {
    //读取 Mesh文件头
    std::ifstream input_file_stream(mesh_file_path, std::ios::in | std::ios::binary);
    MeshFileHead mesh_file_head{};
    input_file_stream.read((char*)&mesh_file_head, sizeof(mesh_file_head));
    //读取顶点数据
    unsigned char* vertex_data = (unsigned char*)malloc(mesh_file_head.vertex_num * sizeof(Vertex));
    input_file_stream.read((char*)vertex_data, mesh_file_head.vertex_num * sizeof(Vertex));
    //读取顶点索引数据
    unsigned short* vertex_index_data = (unsigned short*)malloc(mesh_file_head.vertex_index_num * sizeof(unsigned short));
    input_file_stream.read((char*)vertex_index_data, mesh_file_head.vertex_index_num * sizeof(unsigned short));
    input_file_stream.close();

    mesh_ = new Mesh();
    //mesh_->name = mesh_file_head.name;
    mesh_->vertex_num = mesh_file_head.vertex_num;
    mesh_->vertex_index_num = mesh_file_head.vertex_index_num;
    mesh_->vertex_data = (Vertex*)vertex_data;
    mesh_->vertex_index_data = vertex_index_data;
}

void MeshFilter::CreateMesh(std::vector<Vertex>& vertex_data, std::vector<unsigned short>& vertex_index_data) {
    if (mesh_ != nullptr) {
        delete mesh_;
        mesh_ = nullptr;
    }
    mesh_ = new Mesh();
    mesh_->vertex_num = vertex_data.size();
    mesh_->vertex_index_num = vertex_index_data.size();

    unsigned short vertex_data_size = mesh_->vertex_num * sizeof(Vertex);
    mesh_->vertex_data = static_cast<Vertex*>(malloc(vertex_data_size));
    memcpy(mesh_->vertex_data, &vertex_data[0], vertex_data_size);

    unsigned short vertex_index_data_size = mesh_->vertex_num * sizeof(Vertex);
    mesh_->vertex_index_data = static_cast<unsigned short*>(malloc(vertex_index_data_size));
    memcpy(mesh_->vertex_index_data, &vertex_index_data[0], vertex_index_data_size);
}

void MeshFilter::CreateMesh(std::vector<float>& vertex_data, std::vector<unsigned short>& vertex_index_data) {
    if (mesh_ != nullptr) {
        delete mesh_;
        mesh_ = nullptr;
    }
    mesh_ = new Mesh();
    mesh_->vertex_num = vertex_data.size() / (sizeof(Vertex) / sizeof(float));
    mesh_->vertex_index_num = vertex_index_data.size();

    unsigned short vertex_data_size = mesh_->vertex_num * sizeof(Vertex);
    mesh_->vertex_data = static_cast<Vertex*>(malloc(vertex_data_size));
    memcpy(mesh_->vertex_data, &vertex_data[0], vertex_data_size);

    unsigned short vertex_index_data_size = mesh_->vertex_index_num * sizeof(unsigned short);
    mesh_->vertex_index_data = static_cast<unsigned short*>(malloc(vertex_index_data_size));
    memcpy(mesh_->vertex_index_data, &vertex_index_data[0], vertex_index_data_size);
}

const char* MeshFilter::GetMeshName() {
    return mesh_->name;
}

MeshFilter::~MeshFilter() {
    if (mesh_ != nullptr) {
        delete mesh_;
        mesh_ = nullptr;
    }
}


