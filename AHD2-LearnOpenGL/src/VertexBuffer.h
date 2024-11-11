#pragma once

class  VertexBuffer
{
public:
	VertexBuffer(){}//默认构造函数，给Mesh用
	VertexBuffer(const void* data, unsigned int size);
	~ VertexBuffer();
	void Bind() const;
	void UnBind() const;

private:
	unsigned int m_RendererID;
};
