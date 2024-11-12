#include "VertexArray.h"
#include "Renderer.h"
#include <iostream>

VertexArray::VertexArray()
{
	std::cout << "����vao" << std::endl;
	m_AttributeCount = 0;
	glGenVertexArrays(1, &m_RendererID);
	glBindVertexArray(m_RendererID);
}

VertexArray::~VertexArray()
{
	std::cout << "����vao" << std::endl;
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::AddAtrrib(const VertexBuffer& vertexbuffer, const VertexBufferLayout& vertexbufferlayout)
{
	vertexbuffer.Bind();
	const auto& attributes = vertexbufferlayout.GetAttributes();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < attributes.size(); i++) {
		const auto& singleAttribute = attributes[i];
		glEnableVertexAttribArray(m_AttributeCount + i);
		glVertexAttribPointer(m_AttributeCount + i, singleAttribute.dimension, singleAttribute.type, GL_FALSE, 
			vertexbufferlayout.GetStride(), (void*)offset);//ָ������
		offset += sizeof(singleAttribute.type) * singleAttribute.dimension;
	}
}

void VertexArray::UnBind() const
{
	std::cout << "���vao" << std::endl;
	glBindVertexArray(0);
}
