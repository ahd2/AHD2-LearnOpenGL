#pragma once
#include "vendor/stb_image/stb_image.h"
#include <string>
class Texture
{
public:
	Texture(const std::string& filepath);
	~Texture();
	void Bind(unsigned int index) const;
	void UnBind() const;

private:
	unsigned int m_RendererID;
};