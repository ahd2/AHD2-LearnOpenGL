#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
    VertexBuffer vbo(&vertices[0], vertices.size() * sizeof(Vertex));//创建一个vbo(创建的时候直接绑定了)
    m_Vbo = vbo;
    VertexArray vao;
    VertexBufferLayout layout;
    //注意对齐Vertex结构体
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    vao.AddAtrrib(vbo, layout);
    m_Vao = vao;
    IndexBuffer ibo(&indices[0], indices.size());//创建一个ibo
    m_Ibo = ibo;
    //主动解绑防止后续乱改（可能没必要）
    m_Vao.UnBind();
    m_Ibo.UnBind();
    m_Vbo.UnBind();
}

Mesh::~Mesh()
{
}
