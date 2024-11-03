#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
class  VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void Bind() const;
	void AddAtrrib(const VertexBuffer& vertexbuffer, const VertexBufferLayout& vertexbufferlayout);//ʹ�ó������ñ�֤�޸��ƺ��޸�
	void UnBind() const;

private:
	unsigned int m_RendererID;
	unsigned int m_AttributeCount;
};