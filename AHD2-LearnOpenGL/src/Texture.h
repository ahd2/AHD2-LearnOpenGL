#pragma once
#include "vendor/stb_image/stb_image.h"
#include <string>
class Texture
{
public:
	Texture(const std::string& filepath, unsigned int imageType);
	~Texture();
	void Bind(unsigned int index) const;
	void UnBind() const;

private:
	unsigned int m_RendererID;
	mutable unsigned int m_TexUnitID;//��ǰ�󶨵�����Ԫ��id(�趨Ϊmutableʹ����const�����пɱ��޸�)
};