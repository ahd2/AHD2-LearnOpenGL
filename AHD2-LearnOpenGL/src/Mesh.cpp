#include "Mesh.h"
#include <iostream>
Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
    //VBO
    glGenBuffers(1, &m_Vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    //VAO
    glGenVertexArrays(1, &m_Vao);
    glBindVertexArray(m_Vao);

    // 顶点位置
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // 顶点法线
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3));
    // 顶点纹理坐标
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 6));
    //IBO
    //生成一个缓冲区
    glGenBuffers(1, &m_Ibo);
    //指定为索引缓冲区
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
    //填充当前绑定的索引缓冲区
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    m_IndexCount = indices.size();
    //主动解绑防止后续乱改（可能没必要
    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    //不能在这里删除buffer
    /*glDeleteBuffers(1, &m_Vbo);
    glDeleteBuffers(1, &m_Ibo);
    glDeleteVertexArrays(1, &m_Vao);*/
    std::cout << "析构mesh" << std::endl;
}

void Mesh::Draw(Shader& shader)
{
    glBindVertexArray(m_Vao);
    glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);
}

void Mesh::DeleteBuffer()
{
    glDeleteBuffers(1, &m_Vbo);
    glDeleteBuffers(1, &m_Ibo);
    glDeleteVertexArrays(1, &m_Vao);
}
