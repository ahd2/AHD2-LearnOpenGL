#include "VertexArray.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
	m_AttributeCount = 0;
	glGenVertexArrays(1, &m_RendererID);
	glBindVertexArray(m_RendererID);
}

VertexArray::~VertexArray()
{
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
			vertexbufferlayout.GetStride(), (void*)offset);//指定位置属性
		offset += sizeof(singleAttribute.type) * singleAttribute.dimension;
	}
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);//指定位置属性
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 2));//指定颜色属性
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}
