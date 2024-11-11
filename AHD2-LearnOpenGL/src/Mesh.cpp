#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
    VertexBuffer vbo(&vertices[0], vertices.size() * sizeof(Vertex));//����һ��vbo(������ʱ��ֱ�Ӱ���)
    m_Vbo = vbo;
    VertexArray vao;
    VertexBufferLayout layout;
    //ע�����Vertex�ṹ��
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    vao.AddAtrrib(vbo, layout);
    m_Vao = vao;
    IndexBuffer ibo(&indices[0], indices.size());//����һ��ibo
    m_Ibo = ibo;
    //��������ֹ�����Ҹģ�����û��Ҫ��
    m_Vao.UnBind();
    m_Ibo.UnBind();
    m_Vbo.UnBind();
}

Mesh::~Mesh()
{
}
