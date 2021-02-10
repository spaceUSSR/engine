#include <glad/glad.h>
#include "Renderer/ShaderProgram.h"
#include "mesh.h"

void Mesh::setShader(Renderer::ShaderProgram *shader)
{
	m_shader = shader;
}

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<uint> &indices,
		   const std::vector<Texture> &textures, Renderer::ShaderProgram* shader) :
	m_vertices(vertices), m_indices(indices), m_textures(textures), m_shader(shader)
{
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glGenBuffers(1, &elementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);

	glBufferData(GL_ARRAY_BUFFER, sizeof (Vertex)*m_vertices.size(), value_ptr(m_vertices), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (uint)*m_indices.size(), value_ptr(m_indices), GL_STATIC_DRAW);

	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof (Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof (Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof (Vertex), (void*)offsetof(Vertex, texCoord));
	glEnableVertexAttribArray(2);
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertexBufferObject);
	glDeleteBuffers(1, &elementBufferObject);
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void Mesh::draw()
{
	m_shader->use();
	for(size_t i = 0; i < m_textures.size(); i++)
	{
		m_textures[i].use();
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBindVertexArray(vertexArrayObject);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
}

template<typename T>
DataPtr *Mesh::value_ptr(std::vector<T> &vec)
{
	return  static_cast<DataPtr*>(&vec[0]);
}
