#include "IndexBuffer.h"
#include "Renderer.h"
#include <iostream>
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
{
	std::cout << "构造ibo" << std::endl;
	//生成一个缓冲区
	glGenBuffers(1, &m_RendererID);
	//指定为索引缓冲区
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	//填充当前绑定的索引缓冲区
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
	Count = count;
}

IndexBuffer::~IndexBuffer()
{
	std::cout << "销毁ibo" << std::endl;
	glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::UnBind() const
{
	std::cout << "解绑ibo" << std::endl;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
