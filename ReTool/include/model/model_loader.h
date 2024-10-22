#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <set>
#include <assimp/scene.h>
#include "math/vector2.h"
#include "math/vector3.h"
#include "math/vector4.h"

struct Vertex
{
	Vector3 position{};
	Vector4 color{};
	Vector2 uv{};
};

struct MeshFileHead
{
	char type[4];
	unsigned short vertex_num;
	unsigned short vertex_index_num;
};

struct TextureFileHead
{
	char type_[3];
	int mipmap_level_;
	int width_;
	int height_;
	int gl_texture_format_;
	int texture_size_;
};

struct Mesh {
	unsigned short vertex_num{};
	unsigned short vertex_index_num{};
	Vertex* vertex_data{};
	unsigned short* vertex_index_data{};
};

class ModelFileLoader {
public:
	ModelFileLoader() = default;
	ModelFileLoader(const std::string& path) { LoadModelFile(path); }


	void LoadModelFile(const std::string& path);

	std::vector<std::shared_ptr<Mesh>> meshs;
	std::set<std::string> textures;

	std::filesystem::path directory;
	std::filesystem::path file_name;

private:
	void ProcessNode(aiNode* node, const aiScene* scene);
	std::string LoadMaterialTexturePath(aiMaterial* mat, aiTextureType type);
	void ProcessMesh(aiMesh* mesh, const aiScene* scene);
};

void ExportMeshFile(Mesh* mesh, const std::string& save_path);
bool ConvertImageFile(const std::string& image_file_path, const std::string& save_image_file_path);
