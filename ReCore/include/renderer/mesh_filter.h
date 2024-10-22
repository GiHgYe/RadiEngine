#pragma once

#include <string>
#include <vector>
#include "math/vector2.h"
#include "math/vector3.h"
#include "math/vector4.h"
#include "component/component.h"

REFLECTION_TYPE(MeshFilter)
CLASS(MeshFilter : public Component, WhiteListFields)
{
	REFLECTION_BODY(MeshFilter)
public:
	MeshFilter();
	~MeshFilter();
public:
	struct Vertex {
		Vector3 position;
		Vector4 color;
		Vector2 uv;
	};

	struct MeshFileHead {
		char type[4];
		//char name[32];
		unsigned short vertex_num;
		unsigned short vertex_index_num;
	};

	struct Mesh {
		char* name;
		unsigned short vertex_num;
		unsigned short vertex_index_num;
		Vertex* vertex_data;
		unsigned short* vertex_index_data;

		Mesh() {
			name = nullptr;
			vertex_num = 0;
			vertex_index_num = 0;
			vertex_data = nullptr;
			vertex_index_data = nullptr;
		}

		~Mesh() {
			if (vertex_data != nullptr) {
				delete[] vertex_data;
				vertex_data = nullptr;
			}
			if (vertex_index_data != nullptr) {
				delete[] vertex_index_data;
				vertex_index_data = nullptr;
			}
		}

		unsigned short size() const {
			auto total_bytes = sizeof(vertex_num) + vertex_num * sizeof(Vertex) + sizeof(vertex_index_num) + vertex_index_num * sizeof(unsigned short);
			return total_bytes;
		}
	};

	void LoadMesh(std::string mesh_file_path);

	void CreateMesh(std::vector<Vertex>& vertex_data, std::vector<unsigned short>& vertex_index_data);

	void CreateMesh(std::vector<float>& vertex_data, std::vector<unsigned short>& vertex_index_data);

	Mesh* mesh() { return mesh_; }

	const char* GetMeshName();

private:
	Mesh* mesh_;

};