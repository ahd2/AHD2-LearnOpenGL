#include "VertexBuffer.h"
#include "Renderer.h"
#include <iostream>
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	std::cout << "����vbo" << std::endl;
	//����һ��������
	glGenBuffers(1, &m_RendererID);
	//ָ��Ϊ���㻺����
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	//��䵱ǰ�󶨵Ļ�������������Ķ��㻺������
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	std::cout << "����vbo" << std::endl;
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::UnBind() const
{
	std::cout << "���vbo" << std::endl;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
