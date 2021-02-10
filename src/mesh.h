#ifndef MESH_H
#define MESH_H
#include <glm/glm.hpp>
#include <vector>
#include "Renderer/texture.h"

using Renderer::Texture;
typedef unsigned int uint;
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 texCoord;
};

namespace Renderer {class ShaderProgram;};


typedef void DataPtr;


class Mesh
{
private:
	std::vector<Vertex> m_vertices;
	std::vector<uint> m_indices;
	std::vector<Texture> m_textures;
	Renderer::ShaderProgram* m_shader;

	uint vertexBufferObject;
	uint vertexArrayObject;
	uint elementBufferObject;


	template<typename T>
	static DataPtr* value_ptr(std::vector<T>& vec);
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<uint>& indices,
		 const std::vector<Texture>& textures, Renderer::ShaderProgram* shader = nullptr);
	~Mesh();
	void draw();
	void setShader(Renderer::ShaderProgram *shader);
};


#endif // MESH_H
