#pragma once
#include "GL/glew.h"
#include <vector>

struct VertexBufferSingleAttrib
{
	unsigned int type;//属性数据类型
	unsigned int dimension;//属性的维度
	bool normalized;//是否归一化
};

class  VertexBufferLayout
{
public:
	VertexBufferLayout()
		:m_Stride(0) {};

	template<typename T>
	void Push(unsigned int dimension)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int dimension)
	{
		//目前，是否归一化这个参数默认为false，后续应当做出修改
		m_Attributes.push_back({ GL_FLOAT, dimension, false });
		m_Stride += sizeof(GLfloat) * dimension;
	}

	inline const std::vector<VertexBufferSingleAttrib> GetAttributes() const { return m_Attributes; }

	inline unsigned int GetStride() const { return m_Stride; }
private:
	std::vector<VertexBufferSingleAttrib> m_Attributes;
	unsigned int m_Stride;
};