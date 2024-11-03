#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
class  VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void Bind() const;
	void AddAtrrib(const VertexBuffer& vertexbuffer, const VertexBufferLayout& vertexbufferlayout);//使用常量引用保证无复制和修改
	void UnBind() const;

private:
	unsigned int m_RendererID;
	unsigned int m_AttributeCount;
};