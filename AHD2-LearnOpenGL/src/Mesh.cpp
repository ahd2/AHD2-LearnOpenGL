#include "Mesh.h"
#include <iostream>
Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
    m_Vbo = new VertexBuffer(&vertices[0], vertices.size() * sizeof(Vertex));//创建一个vbo(创建的时候直接绑定了)
    m_Vao = new VertexArray();
    VertexBufferLayout layout;
    //注意对齐Vertex结构体
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    m_Vao->AddAtrrib(*m_Vbo, layout);
    m_Ibo = new IndexBuffer(&indices[0], indices.size());
    //主动解绑防止后续乱改（可能没必要）
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
