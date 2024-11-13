#include "Mesh.h"
#include <iostream>
Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
    m_Vbo = new VertexBuffer(&vertices[0], vertices.size() * sizeof(Vertex));//����һ��vbo(������ʱ��ֱ�Ӱ���)
    m_Vao = new VertexArray();
    VertexBufferLayout layout;
    //ע�����Vertex�ṹ��
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    m_Vao->AddAtrrib(*m_Vbo, layout);
    m_Ibo = new IndexBuffer(&indices[0], indices.size());
    //��������ֹ�����Ҹģ�����û��Ҫ��
    m_Vao->UnBind();
    m_Ibo->UnBind();
    m_Vbo->UnBind();
}

Mesh::~Mesh()
{
}

void Mesh::Draw(Shader& shader)
{
    m_Vao->Bind();
    glDrawElements(GL_TRIANGLES, m_Ibo->Count, GL_UNSIGNED_INT, NULL);
}

void Mesh::DeleteMesh()
{
    delete m_Vao;
    delete m_Vbo;
    delete m_Ibo;
}
