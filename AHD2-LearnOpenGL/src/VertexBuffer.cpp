#include "VertexBuffer.h"
#include "Renderer.h"
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	//����һ��������
	glGenBuffers(1, &m_RendererID);
	//ָ��Ϊ���㻺����
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	//��䵱ǰ�󶨵Ļ�������������Ķ��㻺������
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
