#include "IndexBuffer.h"
#include "Renderer.h"
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
{
	//����һ��������
	glGenBuffers(1, &m_RendererID);
	//ָ��Ϊ����������
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	//��䵱ǰ�󶨵�����������
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}