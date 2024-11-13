#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 Texturecoord;
};

class Mesh
{
public:
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
	~Mesh();
	void Draw(Shader& shader);
	void DeleteMesh();
//private:
	VertexBuffer* m_Vbo;
	VertexArray* m_Vao;
	IndexBuffer* m_Ibo;
};