#pragma once

class  IndexBuffer
{
public:
	 /// <summary>
	 /// 
	 /// </summary>
	 /// <param name="��������"></param>
	 /// <param name="�����ĸ���"></param>
	 IndexBuffer(const unsigned int* data, unsigned int count);
	 IndexBuffer() {}//Ĭ�Ϲ��캯������Mesh��
	~ IndexBuffer();
	void Bind() const;
	void UnBind() const;

private:
	unsigned int m_RendererID;
	unsigned int m_count;
};
