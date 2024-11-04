#include "Texture.h"
#include "Renderer.h"
#include <iostream>
Texture::Texture(const std::string& filepath, unsigned int imageType)
{
    //����
    glGenTextures(1, &m_RendererID);
    //0��Ĭ�ϼ���
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
    m_TexUnitID = 0;
    // Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //����ͼ��
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        //������buffer�������(��ʽ��imageTypeָ��)
        glTexImage2D(GL_TEXTURE_2D, 0, imageType, width, height, 0, imageType, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    //�ͷ�ͼ���ڴ棨cpu�ˣ�
    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(unsigned int index) const
{
    glActiveTexture(GL_TEXTURE0 + index);//����һ������Ԫ����ۣ�
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
    m_TexUnitID = index;
}

void Texture::UnBind() const
{
    glActiveTexture(GL_TEXTURE0 + m_TexUnitID);
    glBindTexture(GL_TEXTURE_2D, 0);
    m_TexUnitID = 0;
}
