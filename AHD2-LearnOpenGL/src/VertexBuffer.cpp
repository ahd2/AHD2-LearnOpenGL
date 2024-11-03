#include "VertexBuffer.h"
#include "Renderer.h"
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	//生成一个缓冲区
	glGenBuffers(1, &m_RendererID);
	//指定为顶点缓冲区
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	//填充当前绑定的缓冲区（即上面的顶点缓冲区）
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
