#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include <vector>
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
	void DeleteBuffer();
private:
	unsigned int m_Vbo;
	unsigned int m_Vao;
	unsigned int m_Ibo;
	unsigned int m_IndexCount;
};