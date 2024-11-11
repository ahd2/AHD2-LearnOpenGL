#pragma once

class  IndexBuffer
{
public:
	 /// <summary>
	 /// 
	 /// </summary>
	 /// <param name="索引数组"></param>
	 /// <param name="索引的个数"></param>
	 IndexBuffer(const unsigned int* data, unsigned int count);
	 IndexBuffer() {}//默认构造函数，给Mesh用
	~ IndexBuffer();
	void Bind() const;
	void UnBind() const;

private:
	unsigned int m_RendererID;
	unsigned int m_count;
};
