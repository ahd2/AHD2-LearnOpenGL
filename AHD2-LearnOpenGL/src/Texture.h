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
	mutable unsigned int m_TexUnitID;//当前绑定的纹理单元的id(设定为mutable使其在const函数中可被修改)
};