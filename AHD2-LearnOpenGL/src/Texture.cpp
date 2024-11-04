#include "Texture.h"
#include "Renderer.h"
#include <iostream>
Texture::Texture(const std::string& filepath, unsigned int imageType)
{
    //纹理
    glGenTextures(1, &m_RendererID);
    //0号默认激活
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
    m_TexUnitID = 0;
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //加载图像
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        //往纹理buffer填充数据(格式用imageType指定)
        glTexImage2D(GL_TEXTURE_2D, 0, imageType, width, height, 0, imageType, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    //释放图像内存（cpu端）
    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(unsigned int index) const
{
    glActiveTexture(GL_TEXTURE0 + index);//激活一号纹理单元（插槽）
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
    m_TexUnitID = index;
}

void Texture::UnBind() const
{
    glActiveTexture(GL_TEXTURE0 + m_TexUnitID);
    glBindTexture(GL_TEXTURE_2D, 0);
    m_TexUnitID = 0;
}
