#include "model/model_loader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <fstream>
#include <codecvt>
#include <iostream>
#include <glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "math/axis_aligned.h"


void ModelFileLoader::LoadModelFile(const std::string& path)
{
	Assimp::Importer import;
	
	const aiScene * scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals); //  | aiProcess_FlipUVs
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "Assimp Error::{}" << import.GetErrorString() << std::endl;
		return;
	}

	directory = std::filesystem::path(path).parent_path();
	file_name = std::filesystem::path(path).stem();

	ProcessNode(scene->mRootNode, scene);
}

void ModelFileLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	Vertex* verties = new Vertex[mesh->mNumVertices];
	unsigned short* indices = new unsigned short[mesh->mNumFaces * 3];
	AxisAlignedBox bounds;

	for (uint32_t i = 0; i < mesh->mNumVertices; i++)
	{
		verties[i].position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };

		if (mesh->HasNormals()) {
			//verties[i].normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
		}

		if (mesh->HasTangentsAndBitangents()) {
			//verties[i].tangent = { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z };
			//verties[i].bi_tangent = { mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z };
		}

		if (mesh->mTextureCoords[0]) {
			verties[i].uv = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
		}
		bounds.Merge(verties[i].position);
	}

	size_t index_count = 0;
	for (uint32_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (uint32_t j = 0; j < face.mNumIndices; j++)
		{
			indices[index_count] = face.mIndices[j];
			++index_count;
		}
	}
	
	std::vector<std::string> mesh_textures;
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::string base_color_texture_file = LoadMaterialTexturePath(material, aiTextureType_DIFFUSE);
		if (!base_color_texture_file.empty()) {
			mesh_textures.push_back(base_color_texture_file);
			textures.insert(base_color_texture_file);
		}
		std::string metallic_roughness_texture_file	= LoadMaterialTexturePath(material, aiTextureType_DIFFUSE_ROUGHNESS);
		if (!metallic_roughness_texture_file.empty()) {
			mesh_textures.push_back(metallic_roughness_texture_file);
			textures.insert(metallic_roughness_texture_file);
		}
		std::string normal_texture_file	= LoadMaterialTexturePath(material, aiTextureType_NORMALS);
		if (!normal_texture_file.empty()) {
			mesh_textures.push_back(normal_texture_file);
			textures.insert(normal_texture_file);
		}
		std::string occlusion_texture_file = LoadMaterialTexturePath(material, aiTextureType_AMBIENT_OCCLUSION);
		if (!occlusion_texture_file.empty()) {
			mesh_textures.push_back(occlusion_texture_file);
			textures.insert(occlusion_texture_file);
		}
		std::string emissive_texture_file = LoadMaterialTexturePath(material, aiTextureType_EMISSIVE);
		if (!emissive_texture_file.empty()) {
			mesh_textures.push_back(emissive_texture_file);
			textures.insert(emissive_texture_file);
		}
	}
	// model name
	//std::wstring_convert< std::codecvt_utf8<wchar_t> > strCnv;
	//std::wstring name = strCnv.from_bytes(mesh->mName.C_Str());
	
	Mesh e_mesh; e_mesh.vertex_num = mesh->mNumVertices; e_mesh.vertex_index_num = index_count;
	e_mesh.vertex_data = verties; e_mesh.vertex_index_data = indices;
	ExportMeshFile(&e_mesh, "./model.mesh");
}

std::string ModelFileLoader::LoadMaterialTexturePath(aiMaterial* mat, aiTextureType type)
{
	std::string texture_file;
	if (mat->GetTextureCount(type) > 0)
	{
		aiString str;
		mat->GetTexture(type, 0, &str);
		texture_file = (directory / str.C_Str()).string();
	}

	if (!texture_file.empty()) ConvertImageFile(texture_file, std::filesystem::path(texture_file).replace_extension(".cpt").string());

	return "";
}

void ModelFileLoader::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (uint32_t i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(mesh, scene);
	}
	for (uint32_t i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

void ExportMeshFile(Mesh* mesh, const std::string& save_path)
{
	std::ofstream output_file_stream(save_path, std::ios::out | std::ios::binary);
	MeshFileHead mesh_file_head{};
	mesh_file_head.type[0] = 'm';
	mesh_file_head.type[1] = 'e';
	mesh_file_head.type[2] = 's';
	mesh_file_head.type[3] = 'h';
	mesh_file_head.vertex_num = mesh->vertex_num;
	mesh_file_head.vertex_index_num = mesh->vertex_index_num;

	output_file_stream.write((char*)&mesh_file_head, sizeof(MeshFileHead));
	output_file_stream.write((char*)mesh->vertex_data, sizeof(Vertex) * mesh->vertex_num);
	output_file_stream.write((char*)mesh->vertex_index_data, sizeof(unsigned int) * mesh->vertex_index_num);

	output_file_stream.close();
}

bool ConvertImageFile(const std::string& image_file_path, const std::string& save_image_file_path)
{
	stbi_set_flip_vertically_on_load(true);

	int channels_in_file, width, height;
	unsigned char* data = stbi_load(image_file_path.c_str(), &width, &height, &channels_in_file, 0);

	int image_data_format = GL_RGB, gl_texture_format = GL_RGB;
	if (data == nullptr) {
		std::cout << image_file_path << " Load image failed.\n";
		return false;
	}

	switch (channels_in_file)
	{
	case 1:
		image_data_format = GL_RED;
		gl_texture_format = GL_COMPRESSED_RED;
		break;
	case 3:
		image_data_format = GL_RGB;
		gl_texture_format = GL_COMPRESSED_RGB;  // GL_COMPRESSED_RGB_S3TC_DXT1_EXT
		break;
	case 4:
		image_data_format = GL_RGBA;
		gl_texture_format = GL_COMPRESSED_RGBA; // GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
		break;
	}

	GLuint gl_texture_id;
	glGenTextures(1, &gl_texture_id);

	glBindTexture(GL_TEXTURE_2D, gl_texture_id);

	glTexImage2D(GL_TEXTURE_2D, 0, gl_texture_format, width, height, 0, image_data_format, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	TextureFileHead tex_head{};
	tex_head.type_[0] = 't';
	tex_head.type_[1] = 'e';
	tex_head.type_[2] = 'x';
	tex_head.mipmap_level_ = 0;
	tex_head.width_ = width;
	tex_head.height_ = height;

	GLint compress_success = 0;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED, &compress_success);

	std::ofstream output_file_stream(save_image_file_path, std::ios::out | std::ios::binary);

	if (compress_success)
	{
		void* image = nullptr;
		GLint compress_size = 0;
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED_IMAGE_SIZE, &compress_size);

		GLint compress_format = 0;
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &compress_format);

		tex_head.gl_texture_format_ = compress_format;
		tex_head.texture_size_ = compress_size;
		//tex_head.compressed = 1;

		image = malloc(compress_size);
		glGetCompressedTexImage(GL_TEXTURE_2D, 0, image);

		output_file_stream.write((char*)&tex_head, sizeof(TextureFileHead));
		output_file_stream.write((char*)image, tex_head.texture_size_);
		free(image);
	}
	else {
		tex_head.gl_texture_format_ = image_data_format;
		tex_head.texture_size_ = height * width * channels_in_file;
		//tex_head.compressed = 0;

		output_file_stream.write((char*)&tex_head, sizeof(TextureFileHead));
		output_file_stream.write((char*)data, tex_head.texture_size_);
		stbi_image_free(data);
	}

	output_file_stream.close();
	return true;
}